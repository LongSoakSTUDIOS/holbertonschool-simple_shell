# The _printf() function

## Contents
```
.
├── README.md
├── main.h
├── _atoi.c
├── _getenv.c
├── _strtok.c
├── fill_buffer.c
├── find_exec.c
├── free_all.c
├── get_full_path.c
├── get_valid_path.c
├── is_builtin.c
├── is_path.c
├── print_env.c
├── signal_handler.c
├── simple_shell.c
├── spawn_child.c
├── tokenize.c
├── hsh
```

## Compile
```
gcc -Wall -Werror -Wextra -pedantic -Wno-format -std=gnu89 *c
```

## Description
This repo contains a simple shell that covers all executables located in /bin as well the the builtin commands listed below in the builtins header. We were also able handle crtl C signal and one input of crtl D.The simple shell was created in a group of 2 over the course of 2 weeks as our final project for C.

## Builtins Available
Available via our shell are the following builtin commands:
- env
- setenv

## Global Variables
- argc
- environ_is_heap
- error_code


## Limitations
### Crtl D
- not working like the shell but even our teachers werent able to understand it
- two Ctrl Ds

### command line history


### setenv override
When you overwrite a variable because you can not diff between a stack and heap allocated. our mimics the glibc which expects a memory leak by popentially losing a pointer by the previously allocated varliable. The checker wants us to solve this but we chose not to.

the laternative to fix this would be to create a data strucutre to hold the previously allocated variables. on exit free those. We felt this was outside of the scope and wanted to the simple shell close to the operating of the glibc shell.

```
==11793== HEAP SUMMARY:
==11793==     in use at exit: 10 bytes in 1 blocks
==11793==   total heap usage: 10 allocs, 9 frees, 2,502 bytes allocated
==11793== 
==11793== LEAK SUMMARY:
==11793==    definitely lost: 0 bytes in 0 blocks
==11793==    indirectly lost: 0 bytes in 0 blocks
==11793==      possibly lost: 0 bytes in 0 blocks
==11793==    still reachable: 10 bytes in 1 blocks
==11793==         suppressed: 0 bytes in 0 blocks
```



### Appeasement of the checker
PATH = ''


## Takeaways
- refactoring of a larger project to make the code work but not for scability
- started the project with a large main that 'worked' so when we started refactioring we found ourselfs passing up to 6 arguments to make a function work like 
- it has been enjoyabled to look deeper into builtin c functionms that we previously took for advantage
- it is extremely clear how on larger projecrts how quickly you can lose track of memory ownership
- naming conventions are still a struggle point for us, when we were refactoring we named things for a single purpoise but then they started being used for mulitple purposes. we feel that we got better on naming the functions post refacotoring.

## Authors

Nick Bath and Jeffrey Mori Ubaldini