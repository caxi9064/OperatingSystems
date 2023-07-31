#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int *list;
    int dim=10,i;
    list=malloc(dim*sizeof(int));
    if(list==NULL)
    {
     printf("Error: no memory");
     exit(1);
    }
   
    for(i=0;i<dim;i++)
    { 
     list[i]=10*i;
     printf(" Value %d == %d \n",i,list[i]);
    }

    free(list);
 
    return EXIT_SUCCESS;
}
