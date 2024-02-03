#ifndef __UNIX_UTILS_H
#define __UNIX_UTILS_H

// Macros section
#define DBG
#define MAX_TOKN 100

// includes section
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef enum {
  OK = 0,
  NOK = -1
}ret_status_t;

// mv function 
ret_status_t my_mv(char *src, char *dest);  
// pwd function
void my_pwd();
// echo function
ret_status_t my_echo(char *str);

#endif // !__UNIX_UTILS_H
