#include "shell.h"

/**
 * _strlen - gets length of a string
 * @str: string
 * Return: length of string
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - compares strings.
 * @string1: 1st string
 * @string2: 2nd string
 * Return: negative when  string1 < string2, positive if string1 > string2, 0 if s1 == s2
 */
int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - * string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @strsearch: string to search
 * @strfind: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *strsearch, const char *strfind)
{
	while (*strfind)
		if (*strfind++ != *strsearch++)
			return (NULL);
	return ((char *)strsearch);
}

/**
 * _strcat - concatenates two strings
 * @deststring: the destination buffer
 * @srcstring: the source buffer
 * Return: destination
 */
char *_strcat(char *deststring, char *srcstring)
{
	char *ret = deststring;

	while (*deststring)
		deststring++;
	while (*srcstring)
		*deststring++ = *srcstring++;
	*deststring = *srcstring;
	return (ret);
}
