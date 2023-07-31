#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int dato_compartido = 0;
int es_par = 0;
pthread_mutex_t m;
pthread_cond_t cL, cV;
        
void pares(void) 
{       
        int i; 
        for(i=0; i < 100; i++ )
        { 
          pthread_mutex_lock(&m);      
          while (es_par==0)
          {
                  pthread_cond_wait(&cL,&m);
          }
          printf("Thread1 = %d \n", dato_compartido++);
          es_par=0;
          pthread_cond_signal(&cV);
          pthread_mutex_unlock(&m);
        }
}


void impares(void)
{
        int i;
        for(i=0; i < 100; i++ )
        {
          pthread_mutex_lock(&m);
          while (es_par==1)
          {
             pthread_cond_wait(&cV,&m);
          }
          printf("Thread2 = %d \n", dato_compartido++);
          es_par=1;
          pthread_cond_signal(&cL);
          pthread_mutex_unlock(&m);
        }
}


int main(void)
{
    pthread_t th1, th2;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cL, NULL);
    pthread_cond_init(&cV, NULL);
    pthread_create(&th1, NULL, pares, NULL);
    pthread_create(&th2, NULL, impares, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cL);
    pthread_cond_destroy(&cV);

}
