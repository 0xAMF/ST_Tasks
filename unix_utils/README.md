# Unix Utils
implementation of pwd, mv and echo shell commands.
**runing the code**
1. mv command
``` bash
gcc mymv.c -o mymv
./mymv <src> <dest>
```
*example:*
``` bash
./mymv test.c testdir/
test.c --> testdir/test.c
```

2. echo command
``` bash
gcc myecho.c -o myecho
./myecho <string>
```
*example:*
```
./myecho hello
hello
```

3. pwd command
``` bash
gcc mypwd.c -o mypwd
./mypwd
```
*example:*
``` bash
./mypwd
/home/afyd/ST_training/tasks/unix_utils
```