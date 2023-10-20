#include "shell.h"


/**
 * unset_alias - sets alias
 * @infor: parameter struct
 * @st: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *infor, char *st)
{
        char *p, c;
        int ret;

        p = _strchr(st, '=');
        if (!p)
                return (1);
        c = *p;
        *p = 0;
        ret = delete_node_at_index(&(infor->alias),
                get_node_index(infor->alias, node_starts_with(infor->alias, st, -1)));
        *p = c;
        return (ret);
}

/**
 * _print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int _print_alias(list_t *node)
{
        char *p = NULL, *a = NULL;

        if (node)
        {
                p = _strchr(node->str, '=');
                for (a = node->str; a <= p; a++)
                        _putchar(*a);
                _putchar('\'');
                _puts(p + 1);
                _puts("'\n");
                return (0);
        }
        return (1);
}

/**
 * _set_alias - sets alias to string
 * @infor: parameter struct
 * @st: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(info_t *infor, char *st)
{
        char *p;

        p = _strchr(st, '=');
        if (!p)
                return (1);
        if (!*++p)
                return (unset_alias(infor, st));

        unset_alias(infor, st);
        return (add_node_end(&(infor->alias), st, 0) == NULL);
}

/**
 * history - display history list.
 * @infor: infor.
 *  Return: Always 0
 */
int history(info_t *infor)
{
	print_list(infor->history);
	return (0);
}


/**
 * alias - alias
 * @inform: inform.
 *  Return: Always 0
 */
int alias(info_t *inform)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (inform->argc == 1)
	{
		node = inform->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inform->argv[i]; i++)
	{
		p = _strchr(inform->argv[i], '=');
		if (p)
			_set_alias(inform, inform->argv[i]);
		else
			_print_alias(node_starts_with(inform->alias, inform->argv[i], '='));
	}

	return (0);
}
