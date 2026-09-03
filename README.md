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
This repo contains a remade printf function that is very limited in scope for Holberton School Australia's integration project. This function was created in a group of 2 over the course of 2 weeks and only covers 6 different formatters which are listed below. During the prototyping phase we were unsure of how to handle the buffer for printf and were deciding between two options, write each character as we encountered it or store them in a linked list and print everything out. At the time we had thought that we wanted to reduce how many times we were calling the write function to reduce processing and had just learned linked lists, so we decided to create it with linked lists. This proved quite challenging process for us and resulted in 12 different scripts to ensure it worked and was mostly compliant with out enforced 'Betty style'. We are happy with the result that we were able to create.

## Formatters
Available via our printf are the following formatters:
-%d, decimals
-%i, integer
-%c, chars
-%s, strings
-%b, binary
-%u, unsigned integer

## Functions

### _printf(const char *format, ...)
This function takes any string and any number of arguments. The arguments will only be invoked given they have a correlating formatter in the string eg (%d , 111). 

Upon successful return, the **_printf()** function returns the number of characters printed. On failure, -1 is returned.

### create_node(string_cont_t **head, char *string_value)
This function takes a double pointer to the head of a linked listed and a string to create a node within a linked list. All formatters with valid content to be printed will have their content converted to a string and then invoke create_node. This function returns a pointer to the new node that is created storing the string it was passed.

### free_nodes(string_cont_t *head)
This function takes a pointer to the head of a linked list and moves through the list freeing the allocated memory until the tail of the list. This function returns nothing.

### store_binary(string_cont_t **head, unsigned int n)
This function takes a double pointer to the head of a linked list and an unsigned int n. It will convert n into a binary number and then into a string to be stored in a node. This function returns a pointer to the new node that is created storing the converted string.

### store_char(string_cont_t **head, char c)
This function takes a double pointer to the head of a linked list and a char c. C will be converted to a string and stored within a node. This function returns a pointer to the new node that is created storing the converted string.

### store_dec(string_cont_t **head, int n)
This function takes a double pointer to the head of a linked list and a integer n. N will be converted to a string and stored within a node. This function returns a pointer to the new node that is created storing the converted string.

### store_string(string_cont_t **head, char *string)
This function takes a double pointer to the head of a linked list and a string string. String gets stored into a node. This function returns a pointer to the new node that is created storing the string. 

### store_unsigned(string_cont_t **head, unsigned int n)
This function takes a double pointer to the head of a linked list and an unsigned integer n. N gets converted into a string and then stored into a node. This function returns a pointer to the new node that is created storing the converted string.

### print_list(string_cont_t *head)
This function takes a pointer to the head of a linked list, moving through each node and writing its string contents to the stdout until the tail. This function returns a int sum, containing the length of each node added together.

## Limitations
### Memory
We have since learnt from our prototyping phase that our approach to printf using linked lists is worse on both memory and processing than it would be simply writing to the stdout for each character. Depending on the input our printf can end up having large amounts of allocated memory taken up just to store a string.

### Non betty complaint
Our _printf() script is the only script that is not complaint with Betty's demand of 'only 40 lines of code per function'. We were able to reduce this number to only 49 lines of code but made the decision that any further refactoring would result in worse code overall.

### Static mallocs
There are 3 instances where we have malloc'd a node and have used a hardcoded static value.

### Complexity
By using linked lists we been able to achieve the same result as our classmates (using only write per character), but have created more scripts and more lines of code. Each time we need to write something to the standard out there needs to be at least 3-4 functions that need to be called. 

## Takeaways
If we were to do this project again, we would spend more time in the prototyping phase understanding the impact that inbuilt function have on a system. We would also chose to let go of our pride and not continue to built a linked list printf just to not waste the 2 hours we spent white boarding.

## Authors

Nick Bath and Jeffrey Mori Ubaldini