#include "shell.h"

/**
 **_memset - memset
 *@ptr:pointer
 *@byt: byt
 *@num: num
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *ptr, char byt, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		ptr[i] = byt;
	return (ptr);
}

/**
 * ffree - ffree
 * @ss: string of strings
 */
void ffree(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc - reallocate block of memory
 * @pt: pointer
 * @oldsize: oldsize
 * @newsize: newsize
 * Return: pointer
 */
void *_realloc(void *pt, unsigned int oldsize, unsigned int newsize)
{
	char *p;

	if (!pt)
		return (malloc(newsize));
	if (!newsize)
		return (free(pt), NULL);
	if (newsize == oldsize)
		return (pt);

	p = malloc(newsize);
	if (!p)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		p[oldsize] = ((char *)pt)[oldsize];
	free(pt);
	return (p);
}
