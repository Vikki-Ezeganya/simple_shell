#include "shell.h"

/**
 * _erratoi - converts string to  integer
 * @str: the string
 * Return: 0 if no numbers in string
 *       -1 on error
 */
int _erratoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - print_error
 * @infor: the parameter & return info struct
 * @est: string containing specified error type
 * Return: 0 if no no. in string, otherwise -1 on error
 */
void print_error(info_t *infor, char *est)
{
	_eputs(infor->fname);
	_eputs(": ");
	print_d(infor->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infor->argv[0]);
	_eputs(": ");
	_eputs(est);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @inputt: the input
 * @fdesc: fdesc to write to
 * Return: no. of characters printed
 */
int print_d(int inputt, int fdesc)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fdesc == STDERR_FILENO)
		__putchar = _eputchar;
	if (inputt < 0)
	{
		_abs_ = -inputt;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inputt;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - convert to number
 * @numb: number
 * @base: base
 * @flag: flag
 * Return: string
 */
char *convert_number(long int numb, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - remove_comments
 * @buff: address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
