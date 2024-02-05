#include "unix_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// mv function 
ret_status_t my_mv(char *src, char *dest)
{
	ret_status_t ret = OK;

	int mv_ret = rename(src, dest);
	if (mv_ret == -1) {
		// check if a directory is passed
		dest = strcat(dest, src);
		mv_ret = rename(src, dest);
		
		if (mv_ret == -1) {
			printf("file does not exit\n");
			ret = NOK;
		}else {
			printf("%s ==> %s\n", src, dest);
		}
	}
	else {
		printf("%s ==> %s\n", src, dest);
	}

	return ret;
}

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
ret_status_t my_echo(char *str)
{
	ret_status_t ret = OK;

	if (str != NULL) {
		printf("%s\n", str);
	} else {
		#ifdef DBG
		printf("NULL pointer error!!\n");
		#endif				/* ifdef DBG */
		ret = NOK;
	}

	return ret;
}
