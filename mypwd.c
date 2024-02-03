 #include <unistd.h>
 #include <stdio.h>



int main(int argc, char * argv[]){
	
	if (argc != 1) {
		printf("usage : %s ", argv[0]);
		return -1;
	}
	unsigned char path[200];
        getcwd(path, 200);

	if (getcwd(path, 200) == NULL) {
		printf("could not get the current working directory \n");
		return -1;
	}
	printf("%s\n", path);
	return 0;
}
