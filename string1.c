#include "shell.h"

/**
 * _strcpy - copies a string
 * @destn: destination
 * @srcc: the source
 * Return: pointer to dest
 */
char *_strcpy(char *destn, char *srcc)
{
	int i = 0;

	if (destn == srcc || srcc == 0)
		return (destn);
	while (srcc[i])
	{
		destn[i] = srcc[i];
		i++;
	}
	destn[i] = 0;
	return (destn);
}

/**
 * _strdup - duplicates a string
 * @st: the string to duplicate
 * Return: duplicated string(pointer)
 */
char *_strdup(const char *st)
{
	int length = 0;
	char *ret;

	if (st == NULL)
		return (NULL);
	while (*st++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--st;
	return (ret);
}

/**
 *_puts - prints input string
 *@st: string
 * Return: null
 */
void _puts(char *st)
{
	int i = 0;

	if (!st)
		return;
	while (st[i] != '\0')
	{
		_putchar(st[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @chr: The character to print
 * Return: success returns 1.
 * for error, -1 is returned
 */
int _putchar(char chr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}
