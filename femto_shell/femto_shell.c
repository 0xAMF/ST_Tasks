#include "unix_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (100)

int main(void)
{
	char *user_input;
	char *arg_vector[MAX];
	char *token;
	int arg_count;
	int i = 0;
	ret_status_t ret = OK;
	
	while (1) {
		arg_count = 0;
		user_input = malloc(1024);
		printf("Alo?! $ ");
		//scanf("%[^\n]", user_input);
		gets(user_input);

		// parse the command
		token = strtok(user_input, " ");
		while (token != NULL) {
			arg_vector[arg_count++] = token;
			token = strtok(NULL, " ");
		}

		if (!strcmp(arg_vector[0], "exit")) {
			printf("Ok, Bye :^)\n");
			exit(0);
		}
		else if(!strcmp(arg_vector[0], "pwd")) {
			if (arg_count != 1) {
				printf("usage: pwd\n");
			}
			else {
				my_pwd();
			}
		}
		else if (!strcmp(arg_vector[0], "mv")){
			if (arg_count != 3) {
				printf("usage: mv <src> <dst>\n");
			}
			else {
				ret = my_mv(arg_vector[1], arg_vector[2]);
			}
		}
		else if (!strcmp(arg_vector[0], "echo")){
			if (arg_count != 2) {
				printf("usage: echo <string>");
			}
			my_echo(arg_vector[1]);
		}
		else {
			printf("command not found!!\n");
		}
	}

	return EXIT_SUCCESS;
}
