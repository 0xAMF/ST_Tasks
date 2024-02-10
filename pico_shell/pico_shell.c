#include "unix_utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IO_WRITE 0


ret_status_t execute(char *command, char **argv, int argc);

char *cwd = NULL;

int max_args = 265;
char *user_input = NULL;
char *new_input = NULL;
char **arg_vector;
char *token;
int arg_count;
int i = 0, counter = 0, new_arg_size = 0;
int input_size, wstatus, execute_ret;
size_t input_buf_size = 1024;
ret_status_t ret = RET_OK;
char esc_seq;


int main(void)
{
	arg_vector = (char **) malloc(max_args * sizeof(char *));
	if (arg_vector == NULL) {
		printf("Couldn't allocate memory for the argument vector\n");
		exit(-1);
	}

	while (1) {
		arg_count = 0;
		my_pwd(&cwd);

		// prompt the user and take input
		printf("Pico@Shell:%s$ ", cwd);
		getline(&user_input, &input_buf_size, stdin);
		if (user_input == NULL) {
			printf("Failed to take input\n");
			exit(-1);
		}

		/* ==== implementing escape sequences ===*/
		for (int i = 0; i < strlen(user_input); i++) {
			if (user_input[i] == '\\') { // in case of backslash
				new_input = user_input + i - 1;
				printf("> ");
				getline(&new_input, &input_buf_size, stdin);
			}
			else if (user_input[i] == '\"' || user_input[i] == '\'') { // in case of double or single quotes
				esc_seq = user_input[i];
				user_input[i] = '\n';
				new_input = user_input + i + 1;
				
				new_arg_size = 0;
				while (1) {
					printf("> ");
					// shift the string buffer
					new_input += new_arg_size;
					getline(&new_input, &input_buf_size, stdin);
					new_arg_size = strlen(new_input);
					// check for the end
					if (user_input[strlen(user_input) - 2] == esc_seq) {
						// to avoid parsing problems when nulling the last character
						user_input[strlen(user_input) - 2] = ' ';
						break;
					}
				}
			}
		}

		// make the last character null instead of \n
		user_input[strlen(user_input) - 1] = 0;
		// if no input is received, only entering enter
		if (strlen(user_input) == 0)
			continue;
		
		// parse the command
		token = strtok(user_input, " \t");
		while (token != NULL) {
			arg_vector[arg_count++] = token;
			token = strtok(NULL, " \t");
		}
		arg_vector[arg_count] = NULL;
		
		// check if exceeded the max argument count
		if (arg_count >= max_args) {
			free(arg_vector);
			max_args *= 1.5;
			arg_vector = (char **)realloc(arg_vector, max_args * sizeof(char *));
			if (arg_vector == NULL) {
				printf("Couldn't reallocate memory for the argument vector\n");
				exit(-1);
			}
		}

	// execute given commands
		ret_status_t ret = execute(arg_vector[0], arg_vector, arg_count);
		if (ret == EXIT) {
			printf("Ok, Bye :^)\n");
			free(cwd);
			free(user_input);
			free(arg_vector);
			exit(EXIT_SUCCESS);
		}
		else if (ret == RET_NOK) {
			printf("Couldn't execute command\n");
			free(cwd);
			free(user_input);
			free(arg_vector);
			exit(-1);
		}
		free(cwd);
	}
	
	free(user_input);
	free(arg_vector);

	return EXIT_SUCCESS;
}

ret_status_t execute(char *command, char **argv, int argc) {
	ret_status_t ret = RET_OK;	
	int wstatus;
	
		// built-in commands commands
		if (!strcmp(argv[0], "exit")) {
			ret = EXIT;
		} else if (!strcmp(argv[0], "pwd")) {
			if (argc != 1) {
				printf("usage: pwd\n");
			} else {
				printf("%s\n", cwd);
			}
		} else if (!strcmp(argv[0], "cd")) {
			if (argc != 2) {
				printf("usage: cd <dest>\n");
			} else {
				ret = cd(argv[1]);
			}
		} else if (!strcmp(argv[0], "echo")) {
			if (argc < 2) {
				printf("usage: echo <string>");
			}
			my_echo(argv, argc);
		} else {
			// check if the command is external
			// fork the process
			pid_t ret_pid = fork();

			if (ret_pid > 0) {	// parent process case
				// wait for child process
				wait(&wstatus);
			} else if (ret_pid == 0) {	// child process case
				// execute process on child 
				int execute_ret = execvp(argv[0], argv);
				if (execute_ret < 0) {
					printf("%s: command not found\n",
					       argv[0]);
					ret = RET_NOK;
				}
			} else {
				printf("Fork failed!\n");
				ret = RET_NOK;
			}
		}
	
	return ret;
}
