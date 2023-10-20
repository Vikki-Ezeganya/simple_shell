#include "shell.h"

/**
 *_eputs - print string
 * @st: st 
 * Return: nill
 */
void _eputs(char *st)
{
	int i = 0;

	if (!st)
		return;
	while (st[i] != '\0')
	{
		_eputchar(st[i]);
		i++;
	}
}

/**
 * _eputchar - prints a character to stderr
 * @ch: The character to print
 * Return: On success 1.
 * error returns -1
 */
int _eputchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * _putfd - writes a character chr to given file descriptor
 * @chr: The character to print
 * @fdesc: The file descriptor to write 
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char chr, int fdesc)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdesc, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}

/**
 *_putsfd - print input string
 * @st: string
 * @fdesc: file descriptor to write to
 * Return: number of chars
 */
int _putsfd(char *st, int fdesc)
{
	int i = 0;

	if (!st)
		return (0);
	while (*st)
	{
		i += _putfd(*st++, fdesc);
	}
	return (i);
}
