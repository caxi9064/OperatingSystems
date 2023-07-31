//P1-SSOO-22/23

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <dirent.h>
#include <string.h>

#define PATH_MAX 4096

int main(int argc, char *argv[])
{

    // ok first, create a char arr that holds the name of the directory
    char directory[PATH_MAX];

    // if less than 1 argument, return the current directory
    if(argc == 1){
        getcwd(directory, sizeof(directory));
    }
    // if exactly 2, valid
    else if (argc == 2){
        strcpy(directory, argv[1]);
    }
    // if not 1 or 2, invalid
    else {
        printf("Error in number of arguments");
        return -1;
    }

    DIR *dir;
    dir = opendir (directory);      // open directory
    if (dir == NULL) {
        printf("Error, Cannot open directory.");
        return -1;
    }

    // directory stream (dirent) used to read and print through
    // the entries in the defined directory
    struct dirent *pDirent;
    while ((pDirent = readdir(dir)) != NULL) {
        printf ("%s\n", pDirent->d_name);
    }

    closedir(dir);      // close directory

	return 0;
}

