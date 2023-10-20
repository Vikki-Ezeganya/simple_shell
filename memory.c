#include "shell.h"

/**
 * bfree - bfree
 * @pt: pt
 * Return: 1 or 0.
 */
int bfree(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
