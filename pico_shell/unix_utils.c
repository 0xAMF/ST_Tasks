#include "unix_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// pwd function
void my_pwd()
{
	int size = 265;
	char *buf = malloc(size);
	char *getcwd_ret;
	char *str_ptr;

	getcwd_ret = getcwd(buf, size);

	if (getcwd_ret != NULL) {
		printf("%s\n", buf);
	} else {
		// allocate enough memory for the pathname string
		while ((getcwd_ret = getcwd(buf, size)) == NULL) {
			free(buf);
			size *= 1.5;
			buf = malloc(size);
		}

		// after allocating enough memory print the pathname
		getcwd_ret = getcwd(buf, size);
		printf("%s\n", buf);
	}
}

// echo function
ret_status_t my_echo(char **argv, int argc)
{
	ret_status_t ret = OK;

	if (argv != NULL) {
		for (int i = 1; i < argc; i++) {
			printf("%s ", argv[i]);
		}
		printf("\n");
	} else {
		printf("NULL pointer error!!\n");
		ret = NOK;
	}

	return ret;
}

ret_status_t cd(char *dir)
{
	ret_status_t ret = OK;
	int chdir_ret;

	chdir_ret = chdir(dir);

	if (chdir_ret == -1) {
		printf("cd: %s: no Such file or directory\n", dir);
		chdir_ret = NOK;
	} else {
		my_pwd();
	}

	return ret;
}
