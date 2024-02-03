#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 265

int main(int argc, char **argv)
{
	char *buf = malloc(SIZE);
	char *getcwd_ret;
	char *str_ptr;
	int newSize = SIZE;

	getcwd_ret = getcwd(buf, SIZE);

	if (getcwd_ret != NULL) {
		printf("%s\n", buf);
	} else {
		// allocate enough memory for the pathname string
		while ((getcwd_ret = getcwd(buf, newSize)) == NULL) {
			free(buf);
			newSize *= 1.5;
			buf = malloc(newSize);
		}

		// after allocating enough memory print the pathname
		getcwd_ret = getcwd(buf, newSize);
		printf("%s\n", buf);
	}

	return EXIT_SUCCESS;
}
