//P1-SSOO-22/23
// will open a file specified as an argument, count the number of lines, words, and bytes of it
#include <stdio.h>
#include <fcntl.h>      // need for sys calls
#include <unistd.h>     // need for read/write sys call

int main(int argc, char *argv[])
{

	//If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
	if(argc < 2)
	{
		printf("Too few arguments\n");
		return -1;
	}

    int fd;
    fd = open(argv[1], O_RDONLY); // open the file and check if exist
    if (fd < 0) {
        printf("File does not exist");
        return -1;
    }
    int lines = 0, words = 0, bytes = 0;
    char letter;

    if (read(fd, &letter, 1) > 0) { // if not empty, add extra line and extra word (the last line and word are not counted)
        lines++;
        words++;
    }
    while (read(fd, &letter, 1) > 0) { // read contents byte by byte
        if (letter == '\n') {
            lines++;
            words++;
        }
        if ((letter == ' ') || (letter == '\t')) {
            words++;
        }
        bytes++;
    }

    close(fd);
    printf("%i %i %i %s", lines, words, bytes, argv[1]);

	return 0;
}
