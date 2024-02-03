#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int path_exist(char *path_name)
{
    struct stat st;
    if (stat(path_name, &st) == 0) {
        return 1;
    } else {
        return 0;
    }
}




int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s src des\n", argv[0]);
        return -1;
    }

    int exist = path_exist(argv[2]);

    char *src_name = basename(argv[1]);

    if (exist != 0) {
        strcat(argv[2], src_name);
    }


    if (rename(argv[1], argv[2]) != 0) {
        printf("could not move the file\n");
        return -1;
    }

    return 0;
}

