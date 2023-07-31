//P1-SSOO-22/23
//searches specific environment variable
//must use calls related to file manipulation: open, read, write, close

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>      // need for sys calls
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{

    /* If less than two arguments (argv[0] -> program, argv[1] -> file to save environment) print an error y return -1 */
    if(argc < 3)
    {
    	printf("Too few arguments\n");
    	return -1;
    }

    int input_fd; 
    input_fd = open("env.txt", O_RDONLY); // open the file env.txt for reading
    if (input_fd < 0) {
        printf("File does not exist");
        return -1;
    }
    
    int output_fd; 
    output_fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644); // open the output file for writing, if already exists clear file and if not create the file
    if (output_fd < 0) {
        printf("File does not exist");
        return -1;
    }

    // It will read the lines one by one and search for the entry with the variable indicated by arguments.
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char *newline_ptr;
    char *var = argv[1];

    // Read the input file line by line and write the lines that contain the variable to the output file
    while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) { // reading the input file in chunks of BUFFER_SIZE bytes at a time
        char *line_start = buffer; 
        while ((newline_ptr = strchr(line_start, '\n')) != NULL) { // searching for the first occurence of \n in the line
            *newline_ptr = '\0'; 
            if (strstr(line_start, var) != NULL) { // searching for the lines containing variable within each chunk
                write(output_fd, line_start, strlen(line_start)); // writing to output file from start of the line
                write(output_fd, "\n", 1);
            }
            line_start = newline_ptr + 1; // incrementing pointer to point to start of line
        }
        if (line_start < buffer + bytes_read && strstr(line_start, var) != NULL) { // case where line is split into two chunks by appending next chunk to prev
            write(output_fd, line_start, strlen(line_start)); // 
        }
    }

    // close the input and output files 
    close(input_fd);
    close(output_fd);

    return 0;
}
