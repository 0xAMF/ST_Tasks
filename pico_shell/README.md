# Femto Shell
Femto shell is a simple shell written in c that supports pwd, mv and echo (for now).

**Building the program**

``` bash
gcc femto_shell.c unix_utils.c -o femto
./femto
```

**Output example**

``` bash
Alo?! $ mv test.c newtest.c
test.c ==> newtest.c
Alo?! $ pwd
/home/afyd/ST_training/tasks/femto_shell
Alo?! $ echo test
test
Alo?! $ exit
Ok, Bye :^)
```

