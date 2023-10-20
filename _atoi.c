#include "shell.h"


/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


/**
 *_isalphabet - checks for alphabetic character
 *@a: The character to input
 *Return: 1 if a is alphabetic, 0 otherwise
 */
int _isalphabet(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 * is_interactive - returns true if shell is interactive mode
 * @infom: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *infom)
{
	return (isatty(STDIN_FILENO) && infom->readfd <= 2);
}



/**
 * is_delimeter - checks if character is a delimeter
 * @d: the char to check
 * @delime: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char d, char *delime)
{
	while (*delime)
		if (*delime++ == d)
			return (1);
	return (0);
}
