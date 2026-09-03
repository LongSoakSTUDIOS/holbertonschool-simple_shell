#include <stddef.h> // NULL
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

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

	//printf("next token at entry: %s\n", next_token);
	while(strchr(delims, src[i]) != NULL && src[i] != '\0')
	{
		src[i] = '\0';
		src++;
		next_token++;
		//printf("next_token middle: %s\n", next_token);
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
	//printf("next_token at exit: %s\n", next_token);
	return (token);
}