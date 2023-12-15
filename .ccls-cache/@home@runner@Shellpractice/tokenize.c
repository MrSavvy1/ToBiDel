#include "shell.h"

/*
 * tokenize - Splits a string into an array of token
 * depending on the given delimeter
 * @str: string to be split
 * @delim: delimiter
 * Return: an array of tokens
 */
char **tokenize(char *str, char *delim)
{
	char **token_arr;
	char *token;
	int i;

	token_arr = malloc(sizeof(char *) * 512);
	if (token_arr == NULL)
		return (NULL);

	token = strtok(str, delim);
	for (i = 0; i < 512 || token != NULL; i++)
	{
		token_arr[i] = token;
		token = strtok(NULL, delim);
	}
	/*
	 * free up excess array space
	* if (i < 1024)
	* {
	*	for (j = i + 1; j < 1024; j++)
	*	{
	*		free(token_arr[j]);
	*	}
	}*
	*/
	free(token);
	return (token_arr);
}
