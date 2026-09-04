#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
/**
 * _strtok - function that tokenizes a string, separating at specified
 * delimiters
 * @src: source string to tokenize
 * @delims: string of valid delimiters
 *
 * Return: returns a pointer to the next valid string, NULL when
 * the src string has ended
 */
char *_strtok(char *src, const char *delims)
{
  	static char *next_token;
  	char *token;
  	int i = 0;
  
  	if (!src)
	{
		if (*next_token == '\0')
			return (NULL);
    	src = next_token;
	}
	else
		next_token = src;
	while(strchr(delims, src[i]) != NULL && src[i] != '\0')
	{
		src[i] = '\0';
		src++;
		next_token++;
	}
	if (src[i] != '\0')
	{
		while (strchr(delims, src[i]) == NULL && src[i] != '\0')
			i++;
		if (src[i] != '\0')
		{
			src[i] = '\0';
			next_token = &src[i + 1];
		}
		else
			next_token = &src[i];
	}
	else
		src = NULL;
	token = src;
	return (token);
}
