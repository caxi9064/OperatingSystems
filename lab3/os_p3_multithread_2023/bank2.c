#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <pthread.h>
#include "queue.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int client_numop = 0; // increment each time a customer performs an operation from a ATM
int bank_numop = 0; // increment each time a worker performs an operation taken from the circular queue shared with the ATMs
int global_balance = 0; // update with each operation, can be pos or neg
int *accountBalanceVector; // will hold account balances, index is the account number

// struct element operation_struct; // declaring struct to store operation data
struct element *list_client_ops; // Array list to store the client operations

queue* circular_queue; // Circular queue

// Function prototypes
void* atm_thread(void* arg);
void* worker_thread(void* arg);

// Mutex for the circular queue and condition variable for the circular queue
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

/**
 * Entry point
 * @param argc
 * @param argv
 * @return
 */
int main (int argc, const char * argv[] ) {
    /* input args format: ./bank <file name> <num ATMs> <num workers> <max accounts> <buff size>
    file_name: corresponds to the file’s path to be imported
    num ATMs: is an integer representing the number of ATMs (producer threads) to be generated
    num workers: is an integer representing the number of workers (consumer threads) to be generated
    max accounts: is a positive integer representing the maximum number of accounts that the bank can have.
    buff size: is an integer indicating the size of the circular queue (maximum number of elements it can store)*/

    // getting the input arguments
    if (argc != 6){ // incorrect number of arguments 
        printf("Correct Input Format: ./bank <file name> <num ATMs> <num workers> <max accounts> <buff size>");
        return 1;
    }
    const char* file_name = argv[1];
    int num_atms = atoi(argv[2]);
    int num_workers = atoi(argv[3]);
    int max_accounts = atoi(argv[4]);
    int buff_size = atoi(argv[5]);

    if (num_atms < 0) {
        printf("num_atms MUST be positive\n");
        return -1;
    }
    if (num_workers < 0) {
        printf("num_workers MUST be positive\n");
        return -1;
    }
    if (max_accounts < 0) {
        printf("max_accounts MUST be positive\n");
        return -1;
    }
    if (buff_size < 0) {
        printf("buff_size MUST be positive\n");
        return -1;
    }
    //num_atms = 1;
    //num_workers = 1; // trick
    accountBalanceVector = malloc(max_accounts * sizeof(int)); // allocating memory to keep track of account balances
    for (int i = 0; i < max_accounts; i++) { // initializing account balance vector
        accountBalanceVector[i] = 0;
    }

    // read file and get operations using scanf 
    FILE *fp;
    char line[1024];
    int max_operations, num_ops = 0;

    fp = fopen(file_name, "r"); // opening file
    if (fp == NULL) { 
        printf("Error opening file: %s\n", file_name);
        return 1;
    }
    if (fgets(line, sizeof(line), fp) == NULL) { // Read the first line to get the maximum number of operations
        printf("Error reading file%s\n", file_name);
        return 1;
    }
    sscanf(line, "%d", &max_operations);
    list_client_ops = malloc(max_operations * sizeof(struct element)); // Allocate memory for the list of operations
    for (int i = 0; i < max_operations; i++) { // initializing list_client_ops with structs
        struct element operation_struct;
        list_client_ops[i] = operation_struct;
    }

    // Read the remaining lines and parse each operation
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (num_ops > max_operations || num_ops > 200){
            break;
        }
        char* token = strtok(line, " ");
        strcpy(list_client_ops[num_ops].type, token); // get operation type
        token = strtok(NULL, " ");
        list_client_ops[num_ops].account1 = atoi(token); // get the account number
        token = strtok(NULL, " ");
        if (token != NULL) { // if no next value then put 0 for account2 and amount
            if (strcmp(list_client_ops[num_ops].type, "TRANSFER") == 0) { // TRANSFER operation
                list_client_ops[num_ops].account2 = atoi(token);
                token = strtok(NULL, " ");
                list_client_ops[num_ops].amount = atoi(token);
            } else { // DEPOSIT or WITHDRAW operation
                list_client_ops[num_ops].amount = atoi(token);
            }
        } else { // CREATE or BALANCE operation
            list_client_ops[num_ops].account2 = 0;
            list_client_ops[num_ops].amount = 0;
        }
        num_ops++;
        list_client_ops[num_ops-1].op_number = num_ops; // adding operation number
    }
    if (num_ops < max_operations){
        printf("%s", "There cannot be fewer operations in the file than the number of operations indicated in the first value");
        free(list_client_ops);
        return 0;
    }

    // Print the parsed operations for debugging
    // for (int i = 0; i < num_ops; i++) {
    //     printf("%d %s %d %d %d\n",list_client_ops[i].op_number, list_client_ops[i].type, list_client_ops[i].account1, list_client_ops[i].account2, list_client_ops[i].amount);
    // }

    fclose(fp); // closing the file

    // Initialize the circular queue
    circular_queue = queue_init(buff_size);

    // printf("%s\n", "atm");
    // Launch the ATMs and the workers
    pthread_t *atm_threads = (pthread_t *)malloc(num_atms*sizeof(pthread_t));
    pthread_t *worker_threads = (pthread_t *)malloc(num_workers*sizeof(pthread_t));
    int *thread_ids = (int*) malloc(num_atms * sizeof(int)); 
    int **args = (int**) malloc(num_atms * sizeof(int)); 

    for (int i = 0; i < num_atms; i++) {
        // printf("%s", "atm");
        thread_ids[i] = i;
        args[i]= (int*) malloc(2 * sizeof(int)); // to hold args to pass to atm_thread
        args[i][0] = i;
        args[i][1] = num_ops;
        if (pthread_create(&atm_threads[i], NULL, atm_thread, (void*) args[i])) {
            printf("%s", "Error: could not create ATM thread\n");
            return 1;
        }
    }
    for (int i = 0; i < num_workers; i++) {
        // printf("%s", "worker");
        thread_ids[i] = i;
        //int *args = (int*) malloc(2 * sizeof(int)); // to hold args to pass to atm_thread
        args[i]= (int*) malloc(2 * sizeof(int)); // to hold args to pass to atm_thread
        args[i][0] = i;
        args[i][1] = num_ops;
        if (pthread_create(&worker_threads[i], NULL, worker_thread, (void*) args[i])) {
            printf("%s","Error: could not create worker thread\n");
            return 1;
        }
    }
    //Wait for the completion of all threads 
    for (int i = 0; i < num_atms; i++) {
        // printf("%s\n", "complete");
        if (pthread_join(atm_threads[i], NULL)) {
            printf("%s","Error: could not complete all threads");
        }
        free(args[i]);
    }
    
    // free memory
    free(list_client_ops); 
    free(accountBalanceVector);
    free(atm_threads);
    free(thread_ids);
    free(args);

    return 0;
}

void* atm_thread(void* arg) {
    int thread_num = *((int*)arg); // getting the thread number
    int num_ops = *((int*)arg + 1); // getting the number of operations
    printf("thread: %d\n", thread_num);
    printf("num_op: %d\n", num_ops);

    // for (int i = 0; i < num_ops; i++){
    //     pthread_mutex_lock(&mutex);
    //     while(queue_full(circular_queue)){
    //         pthread_cond_wait(&empty, &mutex);
    //     }
    //     //printf("adding operation: %s loop var: %d\n", list_client_ops[i].type, i);
    //     // keep track of last operation number
    //     // num_ops not protected 
    //     queue_put(circular_queue, &list_client_ops[i]); // adding operations to queue
    //     client_numop++; // incrementing client_numop
    //     pthread_cond_signal(&full);
    //     pthread_mutex_unlock(&mutex);
    // }
    while(1){
            pthread_mutex_lock(&mutex);
            printf("num ops: %d client op: %d\n", num_ops, client_numop);
            if (client_numop == num_ops){ // reached end of operations, end
                pthread_exit(NULL);
            }
            while(queue_full(circular_queue)){
                pthread_cond_wait(&empty, &mutex);
            }
            //printf("adding operation: %s loop var: %d\n", list_client_ops[i].type, i);
            // keep track of last operation number
            // num_ops not protected 
            queue_put(circular_queue, &list_client_ops[client_numop]); // adding operations to queue
            client_numop++; // incrementing client_numop
            pthread_cond_signal(&full);
            pthread_mutex_unlock(&mutex);
        }

    //pthread_cond_broadcast(&full);  
    pthread_exit(NULL); 
}

void* worker_thread(void* arg) { 
    int thread_num = *((int*)arg);
    int num_ops = *((int*)arg + 1); // getting the number of operations

    while(1){
        pthread_mutex_lock(&mutex); // Lock the mutex before accessing the queue
        
        while (queue_empty(circular_queue)) {
            printf("num ops: %d client op: %d\n", num_ops, client_numop);

            if(client_numop == num_ops){ // no more operation in queue, exit
                //printf("client numop: %d num_ops: %d \n", client_numop, num_ops);
                pthread_exit(NULL);
            }
            pthread_cond_wait(&full, &mutex); // Wait on the full condition variable if the queue is empty
        }

        // extract operation
        struct element* e = queue_get(circular_queue); 
        //printf("getting operation: %s %d %d %d %d\n", e->type, e->account1, e->account2, e->op_number, e->amount);
        char *operation_type = e->type;
        int acc_num1 = e->account1;
        int acc_num2 = e->account2;
        int operation_num = e->op_number;
        int amount = e->amount;

        // Perform Operations
        // print operation number, operation type, arguments, account balance, global bank balance
        if (strcmp(operation_type,"CREATE") == 0){ // Create
            accountBalanceVector[acc_num1] += 0; // update account balance
            global_balance += amount; // update global balance
            printf("%d %s %d BALANCE=%d TOTAL=%d \n", operation_num, operation_type, acc_num1, accountBalanceVector[acc_num1], global_balance);
        } 
        else if (strcmp(operation_type, "DEPOSIT") == 0){ // Deposit
            accountBalanceVector[acc_num1] += amount; // update account balance
            global_balance += amount; // update global balance
            printf("%d %s %d %d BALANCE=%d TOTAL=%d \n", operation_num, operation_type, acc_num1, amount, accountBalanceVector[acc_num1], global_balance);
        }
        else if (strcmp(operation_type, "BALANCE") == 0){ // Balance
            printf("%d %s %d BALANCE=%d TOTAL=%d \n", operation_num, operation_type, acc_num1, accountBalanceVector[acc_num1], global_balance);
        }
        else if (strcmp(operation_type, "WITHDRAW") == 0){ // Withdraw
            // if (accountBalanceVector[acc_num1] >= amount) { // cannot be negative
            //     accountBalanceVector[acc_num1] -= amount;
            //     global_balance -= amount;
            //     printf("%d %s %d %d BALANCE=%d TOTAL=%d \n", operation_num, operation_type, acc_num1, amount, accountBalanceVector[acc_num1], global_balance);
            // } 
            accountBalanceVector[acc_num1] -= amount;
            global_balance -= amount;
            printf("%d %s %d %d BALANCE=%d TOTAL=%d \n", operation_num, operation_type, acc_num1, amount, accountBalanceVector[acc_num1], global_balance);
            // else {
            //     printf("Operation %s: Insufficient funds in account %d for withdrawal of %d\n", operation_type, acc_num1, amount);
            // }
        }
        else if (strcmp(operation_type, "TRANSFER") == 0){ // Transfer
            // if (accountBalanceVector[acc_num1] >= amount) {
            //     accountBalanceVector[acc_num1] -= amount;
            //     accountBalanceVector[acc_num2] += amount;
            //     printf("%d %s %d %d %d BALANCE=%d TOTAL=%d \n", operation_num, operation_type, acc_num1, acc_num2, amount, accountBalanceVector[acc_num2], global_balance);
            // }
            accountBalanceVector[acc_num1] -= amount;
            accountBalanceVector[acc_num2] += amount;
            printf("%d %s %d %d %d BALANCE=%d TOTAL=%d \n", operation_num, operation_type, acc_num1, acc_num2, amount, accountBalanceVector[acc_num2], global_balance); 
            // else {
            //     printf("Operation %s: Insufficient funds in account %d for transfer of %d to account %d\n", operation_type, acc_num1, amount, acc_num2);
            // }
        }
        bank_numop++;
        
        // Unlock the mutex and signal the empty condition variable
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    //pthread_cond_broadcast(&empty);  
    pthread_exit(NULL);
}