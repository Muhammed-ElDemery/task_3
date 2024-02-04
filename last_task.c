#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>


int find_indx(char command[], int size, char result_1[], char result_2[])
{
    //  strcpy(result_1, "");
    //strcpy(result_2, "");

    result_1[0] = '\0';
    result_2[0] = '\0';

    int counter = 0;
    int goal = 0;
    int exist = 0;
    int no_space = 1;



    for (counter = 0; counter < size; counter++) {
	if (command[counter] == ' ') {
	    goal = counter;
	    no_space = 0;
	    break;
	}
    }
    if (no_space == 0) {
	for (counter = 0; counter < goal; counter++) {
	    result_1[counter] = command[counter];
	}
	result_1[goal] = '\0';

    } else {
	strcpy(result_1, command);
	return 0;
    }



    for (counter = goal + 1; counter < size; counter++) {
	if (command[counter] == ' ') {
	    exist++;
	}
	result_2[counter - goal - 1] = command[counter];
    }
    result_2[counter - goal - 1] = '\0';



    if (!((result_2[0] == '\'' && result_2[strlen(result_2) - 1] == '\'')
	  || (result_2[0] == '"' && result_2[strlen(result_2) - 1] == '"')
	  || (result_2[0] != '\'' && result_2[0] != '"'
	      && result_2[strlen(result_2) - 1] != '\''
	      && result_2[strlen(result_2) - 1] != '"')))
	return -1;


    if (result_2[0] != '\'' && result_2[0] != '"' &&
	result_2[strlen(result_2) - 1] != '\''
	&& result_2[strlen(result_2) - 1] != '"' && exist != 0) {
	return -1;
    }
    return 0;
}




//___________________________________________________________________________________________________________________________________________________________________


int main()
{



    printf
	("-----------------------------------------------------------------  Welcome to femto shell :) ---------------------------------------------------------------------\n\n\n\n\n");

    char command[200];
    char result_1[50];
    char result_2[200];
    char exit[5] = "exit";
    char cd[3] = "cd";
    char pwd[4] = "pwd";
    char echo[5] = "echo";
    int test = 1;
    int ret_val = 0;

    while (test) {
	command[0] = '\0';
	printf
	    ("*************************************************************************************\n");

	fgets(command, sizeof(command), stdin);
	if (command[strlen(command) - 1] == '\n')
	    command[strlen(command) - 1] = '\0';
	ret_val = find_indx(command, strlen(command), result_1, result_2);

	if (ret_val == -1) {
	    printf("invalid argument\n");
	    continue;
	}

	test = strcmp(result_1, exit);
	if (test == 0)
	    if (strlen(result_2) == 0)
	        break;
	    else {
	        printf("usage: %s\n", exit);
	        test = 1;
		continue;
	    }
	if (strcmp(result_1, pwd) == 0) {
	    if (strlen(result_2) != 0) {
		printf("usage : %s \n", result_1);
		continue;
	    }

	    unsigned char path[200];
	    getcwd(path, 200);
	    if (getcwd(path, 200) == NULL) {
		printf("could not get the current working directory \n");
		return -1;
	    }
	    printf("%s\n", path);

	} else if (strcmp(result_1, echo) == 0) {

	    int count = 0;
	    for (count = 0; count < strlen(result_2); count++)
		if (result_2[count] == '\'' || result_2[count] == '"')
		    continue;
		else
		    printf("%c", result_2[count]);
	    printf("\n");

	} else if (strcmp(result_1, cd) == 0) {

	    int ret_cd = chdir(result_2);
	    if (ret_cd != 0) {
		printf("could not reach the path\n");
	    }
	} else {
	    printf("this femto shell does not support this command\n");
	}

    }


    printf("good bye! \n");

    return 0;
}
