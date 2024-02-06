#ifndef __UNIX_UTILS_H
#define __UNIX_UTILS_H

// Macros section
#define DBG

// includes section
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef enum {
  OK = 0,
  NOK = -1
}ret_status_t;

// mv function 
ret_status_t my_mv(char *src, char *dest);  
// pwd function
char* my_pwd();
// echo function
ret_status_t my_echo(char **argv, int argc);
// cd function
ret_status_t cd(char *dir);

#endif // !__UNIX_UTILS_H
