#include <stdio.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char *argv[])
{
    if (argc != 2) {
	printf("usage: %s 'string you want to print\n'", argv[0]);
	return -1;
    }
    int num_read, num_write;
    num_write = write(1, argv[1], strlen(argv[1]));
    if (num_read > 0) {
	printf("could not print the output \n");
	return -1;
    }

    printf("\n");
    return 0;
}
