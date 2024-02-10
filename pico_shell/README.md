# Pico Shell
Pico shell is an updated version of femto shell which is a simple shell written in c that supports pwd, cd and echo and now supporting external commands from linux.

**Building the program**

``` bash
gcc pico_shell.c unix_utils.c -o pico
./pico
```
**Supported Features**
* cd, pwd and echo internal commands
* Executing external commands located in PATH
* escape sequences (", ', \\)
**Output example**

![](https://github.com/0xAMF/ST_Tasks/blob/main/pico_shell/test_cases/picoshell_test.mov)
