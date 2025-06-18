#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>

char* slicing_index(char* string, int start, int end) {
	char *substring = (char *)malloc(sizeof(char)*100);
	for (int i = start; i < end; i++) {
		substring[i-start] = string[i];
	}

	substring[end-start] = '\0';

	return substring;
}

int wordCountIgnoreNewLine(char* file_name) {

	FILE *fptr;
	char file_content[1000];
	char ch;
	int count = 0;

	fptr = fopen(file_name, "r");

	if (fptr == NULL) {
		perror("FileDoesNotExistError");
		return 1;
	}
	else {
		int i = 0;

		do {
			ch = fgetc(fptr);
			file_content[i] = ch;

			if (file_content[i] == ' ') {
				if (i == 0) continue;

				if (file_content[i-1] != ' ' && file_content[i-1] != '\n') count++;
			}

			else if (file_content[i] == '\n') {
				if (i == 0) continue;

				if (file_content[i-1] == ' ' || file_content[i-1] == '\n') continue;

				count++;
			}
			i++;

		} while (ch != EOF);

		if (file_content[strlen(file_content)-1] != ' ') count++;

		fclose(fptr);
		return count;
	}

	return 0;
}

int wordCount(char* file_name) {

	FILE *fptr;
	char file_content[1000];
	char ch;
	int count = 0;

	fptr = fopen(file_name, "r");

	if (fptr == NULL) {
		perror("FileDoesNotExistError");
		return 1;
	}
	else {
		int i = 0;

		do {
			ch = fgetc(fptr);
			file_content[i] = ch;

			if (ch == ' ') {
				if (i == 0) continue;

				if (file_content[i-1] == '\n') {
					if (i == 1) count++;

					else if (file_content[i-2] == ' ') count++;
				}

				if (file_content[i-1] != ' ') count++;
			}

			else if (ch == '\n') {
				if (i == 0) continue;

				if (file_content[i-1] == ' ') continue;

				count++;
			}
			i++;

		} while (ch != EOF);

		if (file_content[strlen(file_content)-1] != ' ') count++;

		fclose(fptr);
		return count;
	}

	return 0;
}

int wordCommand(char* command) {

	char *file_name, *file1_name, *file2_name;
	int count, count_file1, count_file2, count_diff;

	if (command[5] != '-') {
		file_name = slicing_index(command, 5, strlen(command));
		count = wordCount(file_name);
		printf("Number of Words in File: %d \n", count);
	}

	else if ((command[5] == '-' && command[8] == '-') || (command[5] == '-' && command[7] == '-')) {
		printf("Only one Mode can be used at a Time!\n");
	}

	else if (command[6] == 'n') {
		file_name = slicing_index(command, 8, strlen(command));
		count = wordCountIgnoreNewLine(file_name);
		printf("Number of Words in File: %d \n", count);
	}

	else if (command[6] == 'd') {
		int space_index;

		for (int i = 8; i < strlen(command); i++) {
			if (command[i] == ' ') {
				space_index = i;
				break;
			}
		}

		file1_name = slicing_index(command, 8, space_index);
		file2_name = slicing_index(command, space_index+1, strlen(command));

		count_file1 = wordCount(file1_name);
		count_file2 = wordCount(file2_name);

		count_diff = (count_file1 > count_file2) ? (count_file1 - count_file2) : (count_file2 - count_file1);

		printf("Word Count Difference between these two files: %d \n", count_diff);
	}

	else
		printf("Incorrect Command Entered");

	return 0;

}

int main(int argv, char **argc) {
	printf("\nWELCOME TO BBOsh TERMINAL\n");
	printf("-------------------------\n");
	char *flag_caption;
	flag_caption = "0";

	while (1) {

		pid_t pid;
		char input[100];
		char *sentence;
		printf("\nBBOsh > ");
		fgets(input, sizeof(input), stdin);
		// printf("'%s' \n", sentence);
		sentence = slicing_index(input, 0, strlen(input)-1);

		if (!strcmp(sentence, "dir -v")) {
			printf("Caption Messages: ON\n");
			flag_caption = "1";
			continue;
		}

		if (!strcmp(sentence, "exit"))
			break;

		pid = fork();

		if (pid > 0) {
			wait(NULL);
			continue;
		}

		else if (pid == 0) {

			char *command = (char *)malloc(sizeof(char)*10);
			command = slicing_index(sentence, 0, 4);
			// printf("'%s' \n", command);

			if (!strcmp(command, "word")) {
				wordCommand(sentence);
			}

			else if (!strcmp(command, "dir ")) {
				if (sentence[4] == '-' && sentence[6] == ' ') {
					char *mode;
					mode = slicing_index(sentence, 4, 6);

					char *file_name;
					file_name = slicing_index(sentence, 7, strlen(sentence));
					
					char *args[] = {"./DIR", mode, file_name, flag_caption, NULL};
					execvp(args[0], args);
				}
				else {
					char *file_name;
					file_name = slicing_index(sentence, 4, strlen(sentence));

					char *args[] = {"./DIR", file_name, flag_caption, NULL};
					execvp(args[0], args);
				}

			}

			else if (!strcmp(command, "date")) {
				if (sentence[5] == '-' && sentence[7] == ' ') {
					char *mode;
					mode = slicing_index(sentence, 5, 7);

					char *file_name;
					file_name = slicing_index(sentence, 8, strlen(sentence));
					
					char *args[] = {"./DATE", mode, file_name, NULL};
					execvp(args[0], args);
				}
				else {
					char *file_name;
					file_name = slicing_index(sentence, 5, strlen(sentence));

					char *args[] = {"./DATE", file_name, NULL};
					execvp(args[0], args);
				}

			}

			else
				printf("Command does not Exist!");

			exit(0);
			// return(0);
		}

		else {
			perror("Error in Fork");
			return 1;
		}

	}

	printf("\n-------------------------\n");
	printf("TERMINATED\n\n");

	return 0;
}