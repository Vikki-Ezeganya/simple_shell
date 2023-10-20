#include "shell.h"

/**
 * add_node - add_node
 * @header: header
 * @st: st
 * @numb: index of node
 * Return: list size
 */
list_t *add_node(list_t **header, const char *st, int numb)
{
	list_t *new_head;

	if (!header)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = numb;
	if (st)
	{
		new_head->str = _strdup(st);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *header;
	*header = new_head;
	return (new_head);
}

/**
 * add_node_end - add node to list end
 * @header: header
 * @st: st
 * @numb: numb
 * Return: list size
 */
list_t *add_node_end(list_t **header, const char *st, int numb)
{
	list_t *new_node, *node;

	if (!header)
		return (NULL);

	node = *header;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = numb;
	if (st)
	{
		new_node->str = _strdup(st);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*header = new_node;
	return (new_node);
}

/**
 * print_list_str - print_list_str
 * @ptr: first node  pointer
 * Return: list size
 */
size_t print_list_str(const list_t *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - delete_node_at_index
 * @header: header
 * @indx: indx
 * Return: 1 OR 0 on failure
 */
int delete_node_at_index(list_t **header, unsigned int indx)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!header || !*header)
		return (0);

	if (!indx)
	{
		node = *header;
		*header = (*header)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *header;
	while (node)
	{
		if (i == indx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - free_list
 * @headptr: head node pointer
 * Return: void
 */
void free_list(list_t **headptr)
{
	list_t *node, *next_node, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*headptr = NULL;
}
