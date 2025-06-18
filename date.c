#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>

int main(int argv, char **argc) {
	if (argv == 2) {
		char t[100];
		struct stat b;
		if (!stat(argc[1], &b)) {
			strftime(t, 100, "%d/%m/%Y %H:%M:%S", localtime( &b.st_mtime));
			printf("Last Modified Date and Time: %s \n", t);
		}
		else {
			perror("Internal Error while extracting Last Modified Date");
			return 1;
		}
	}

	else if (argv == 3) {
		if (!strcmp(argc[1], "-R")) {
			char t[100];
			struct stat b;
			if (!stat(argc[2], &b)) {
				strftime(t, 100, "%a, %d %b %Y %T %z", localtime( &b.st_mtime));
				printf("Last Modified Date and Time: %s \n", t);
			}
			else {
				perror("Internal Error while extracting Last Modified Date");
				return 1;
			}
		}
	}

	return 0;
}