#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100
#define FILE_PERMESSION 0644

int main(int argc, char **argv)
{
	// declare variables used
	int fd1, fd2, write_count, read_count, remove_ret;
	char buf[BUF_SIZE];
	char *src = argv[1];
	char *dest = argv[2];

	if (argc != 3) {
		printf("usage: ./mymv <source> <destination>\n");
		return 1;
	}
	// open first file
	fd1 = open(src, O_RDONLY);
	if (fd1 < 0) {
		printf("Couldn't open %s\n", src);
		return -1;
	}
	// create the second file
	fd2 = creat(dest, FILE_PERMESSION);
	if (fd2 < 0) {
		// if the name is not specified (moving the file)
		// check if the dest is a directory, then concat the dir name with the file name 
		dest = strcat(dest, src);
		fd2 = creat(dest, FILE_PERMESSION);
		
		if (fd2 < 0) {
			printf("Couldn't open %s\n", argv[2]);
			return -1;
		}
	}
	// read first file
	while ((read_count = read(fd1, buf, BUF_SIZE)) != 0) {
		if (read_count < 0) {
			printf("couldn't read %s\n", argv[1]);
			return -1;
		}
		// write on second file 
		write_count = write(fd2, buf, BUF_SIZE);
		if (write_count < 0) {
			printf("couldn't write on %s\n", argv[2]);
			return -1;
		}
	}

	// remove first file
	if ((remove_ret = remove(src)) < 0) {
		printf("couldn't move/rename %s\n", src);
		return -1;
	}


	printf("%s ---> %s\n", src, dest);

	close(fd1);
	close(fd2);
 
	// we could also use rename syscall.

	return EXIT_SUCCESS;
}
