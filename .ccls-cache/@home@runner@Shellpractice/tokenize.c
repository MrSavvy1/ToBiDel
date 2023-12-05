#include "shell.h"
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
				char str[] = "This is a test string  ";
				char delim[] = " ";
				char **tokens = tokenize(str, delim);

				int i = 0;
				while (tokens[i] != NULL) {
								printf("Token %d: %s\n", i, tokens[i]);
								i++;
				}

				// Free the memory for tokens
				for (int j = 0; tokens[j] != NULL; j++) {
								free(tokens[j]);
				}
				free(tokens);

				return 0;
}*/


/**
	* tokenize - Splits a string into an array of tokens
	* depending on the given delimiter
	* @str: string to be split
	* @delim: delimiter
	* Return: an array of tokens
	*/
char **tokenize(char *str, char *delim)
{
				char **token_arr = malloc(sizeof(char *));
				if (token_arr == NULL || str == NULL || delim == NULL)
								return NULL;

				char *token = strtok(str, delim);
				int i = 0;

				while (token != NULL)
				{
								token_arr = realloc(token_arr, (i + 2) * sizeof(char *));
								if (token_arr == NULL)
								{
												free(token);
												return NULL; // Allocation failure
								}

								token_arr[i] = token;
								i++;

								token = strtok(NULL, delim);
				}

				token_arr[i] = NULL; // Terminate the array

				return token_arr;
}
