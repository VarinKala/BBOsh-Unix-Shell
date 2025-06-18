#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>

int main(int argv, char **argc) {
	DIR* dir;

	if (argv == 3) {
		dir = opendir(argc[1]);

		if (dir) {
			perror("DirectoryExistsError: Directory already exists");
			return 1;
		} 
		else if (ENOENT == errno) {
			mkdir(argc[1], 0777);
			chdir(argc[1]);
			if (!strcmp(argc[2],"1")) {
				printf("New Directory Created!\n");
			}
		}
		else {
			perror("Internal Error while searching for Directory");
			return 1;
		}
	}

	else if (argv == 4) {
		if (strcmp(argc[1], "-r")) {
			perror("Syntax Error: Mode Does Not Exist");
			return 1;
		}

		dir = opendir(argc[2]);

		if (dir) {
			if (rmdir(argc[2])) {
				if (!strcmp(argc[3],"1"))
					printf("Removing Already Existing Directory\n");
			}

			mkdir(argc[2], 0777);
			chdir(argc[2]);
			if (!strcmp(argc[3],"1")) {
				printf("New Directory Created!\n");
			}
		} 
		else if (ENOENT == errno) {
			mkdir(argc[2], 0777);
			chdir(argc[2]);
			if (!strcmp(argc[3],"1")) {
				printf("New Directory Created!\n");
			}
		}
		else {
			perror("Internal Error while searching for Directory");
			return 1;
		}
	}

	return 0;

}