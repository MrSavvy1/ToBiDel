#include "shell.h"

/**
 * in_path - checks env variable PATH if file exist
 *
 * @filename: filename to check
 *
 * Return: 1 if filename in PATH else 0
 */
char *in_path(char *filename)
{
	int i;
	char *path, **token_arr, full_path[1024], *path_cpy, *ret_path;
	struct stat statbuf;

	/* This line returns a pointer to a string within the environment list
	 * this string must not be modified by the caller
	 */
	path = getenv("PATH");
	if (!path)
		return (NULL);

	/* This is why you should get a duplicate or a copy of the string */
	path_cpy = strdup(path);

	token_arr = tokenize(path_cpy, ":");

	full_path[0] = '\0';
	i = 0;
	while(token_arr[i])
	{
		strcpy(full_path, token_arr[i]);
		strcat(full_path, "/");
		strcat(full_path, filename);
		if (stat(full_path, &statbuf) == 0)
		{
			ret_path = NULL;
			ret_path = strdup(full_path);
			return (ret_path);
		}
		i++;
	}
	free(path_cpy);
	free(token_arr);
	return (NULL);
}
