
#include "shell.h"

/**
 * list_len - list_len
 * @pt: pt
 * Return: list size
 */
size_t list_len(const list_t *pt)
{
	size_t i = 0;

	while (pt)
	{
		pt = pt->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - list_to_strings
 * @header: header
 * Return: [] of strings
 */
char **list_to_strings(list_t *header)
{
	list_t *node = header;
	size_t i = list_len(header), j;
	char **strs;
	char *str;

	if (!header || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - print_list
 * @ptr: ptr
 * Return:list size
 */
size_t print_list(const list_t *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		_puts(convert_number(ptr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - node_starts_with
 * @node: pointer to list head
 * @prfx: prfx
 * @chr: chr
 * Return: node or null
 */
list_t *node_starts_with(list_t *nodee, char *prfx, char chr)
{
	char *p = NULL;

	while (nodee)
	{
		p = starts_with(nodee->str, prfx);
		if (p && ((chr == -1) || (*p == chr)))
			return (nodee);
		nodee = nodee->next;
	}
	return (NULL);
}

/**
 * get_node_index - get_node_index
 * @header: header
 * @nodee: nodee
 * Return: node or -1
 */
ssize_t get_node_index(list_t *header, list_t *nodee)
{
	size_t i = 0;

	while (header)
	{
		if (header == nodee)
			return (i);
		header = header->next;
		i++;
	}
	return (-1);
}
