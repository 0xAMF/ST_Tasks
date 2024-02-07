#include "unix_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX (100)

int main(void)
{
	char *user_input = NULL;
	char *cwd = NULL;
	char *arg_vector[MAX];
	char *token;
	int arg_count;
	int i = 0, counter = 0;
	int input_size, wstatus, execute_ret;
	size_t input_buf_size = 1024;
	ret_status_t ret = OK;
	char *new_input;

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

		// implementing escape sequence
		for (int i = 0; i < strlen(user_input); i++) {
			if (user_input[i] == '\\') {
				new_input = user_input + i;
				counter += i;
				while (1) {
					printf("> ");
					getline(&new_input, &input_buf_size, stdin);
					if (user_input[strlen(user_input) - 1] == '\n') {
						break;
					}
				}
			}
		}
		
		input_size = strlen(user_input);
		user_input[input_size - 1] = 0;

		// if no input is received, only entering enter
		if (input_size == 1)
			continue;

		// parse the command
		token = strtok(user_input, " ");
		while (token != NULL) {
			arg_vector[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		arg_vector[arg_count] = NULL;

		// built-in commands commands
		if (!strcmp(arg_vector[0], "exit")) {
			printf("Ok, Bye :^)\n");
			exit(0);
		} else if (!strcmp(arg_vector[0], "pwd")) {
			if (arg_count != 1) {
				printf("usage: pwd\n");
			} else {
				printf("%s\n", cwd);
			}
		} else if (!strcmp(arg_vector[0], "cd")) {
			if (arg_count != 2) {
				printf("usage: cd <dest>\n");
			} else {
				ret = cd(arg_vector[1]);
			}
		} else if (!strcmp(arg_vector[0], "echo")) {
			if (arg_count < 2) {
				printf("usage: echo <string>");
			}
			my_echo(arg_vector, arg_count);
		} else {
			// check if the command is external
			// fork the process
			pid_t ret_pid = fork();

			if (ret_pid > 0) {	// parent process case
				// wait for child process
				wait(&wstatus);
			} else if (ret_pid == 0) {	// child process case
				// execute process on child 
				execute_ret = execvp(arg_vector[0], arg_vector);
				if (execute_ret < 0) {
					printf("%s: command not found\n",
					       arg_vector[0]);
					free(cwd);
					free(user_input);
					exit(-1);
				}
			} else {
				printf("Fork failed!\n");
			}
		}

		free(cwd);
	}

	free(user_input);

	return EXIT_SUCCESS;
}

