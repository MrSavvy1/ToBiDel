#include "shell.h"

/**
 * _strcmp - This function compares two string
 * @s1: The first string to compare
 * @s2: The second string to compare
 * Return: 0 if the two strings are equall and 1 if false
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
