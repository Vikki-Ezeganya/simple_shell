#include "shell.h"

/**
 **_strncpy - copies a string
 *@destn: the destination string to be copied to
 *@sr: source string
 *@numchr: no. of characters to be copied
 *Return: string
 */
char *_strncpy(char *destn, char *sr, int numchr)
{
	int i, j;
	char *s = destn;

	i = 0;
	while (sr[i] != '\0' && i < numchr - 1)
	{
		destn[i] = sr[i];
		i++;
	}
	if (i < numchr)
	{
		j = i;
		while (j < numchr)
		{
			destn[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - _strncat
 *@destn: destination string
 *@sr: second str
 *@num: bytes to be used
 *Return: the concatenated string
 */
char *_strncat(char *destn, char *sr, int num)
{
	int i, j;
	char *s = destn;

	i = 0;
	j = 0;
	while (destn[i] != '\0')
		i++;
	while (sr[j] != '\0' && j < num)
	{
		destn[i] = sr[j];
		i++;
		j++;
	}
	if (j < num)
		destn[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@str: the string to be parsed
 *@chr: character
 *Return: pointer
 */
char *_strchr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
