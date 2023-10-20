#include "shell.h"

/**
 * is_chain - is_chain
 * @infom: infom
 * @buffer: the char buffer
 * @pos: address of current position in buf
 * Return: 1 OR 0 
 */
int is_chain(info_t *infom, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		infom->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		infom->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		infom->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * check_chain - check_chain
 * @infom: infom
 * @buffer: char buff
 * @pd: address of current position in buf
 * @l: starting position in buf
 * @length: length
 * Return: Void
 */
void check_chain(info_t *infom, char *buffer, size_t *pd, size_t l, size_t length)
{
	size_t j = *pd;

	if (infom->cmd_buf_type == CMD_AND)
	{
		if (infom->status)
		{
			buffer[l] = 0;
			j = length;
		}
	}
	if (infom->cmd_buf_type == CMD_OR)
	{
		if (!infom->status)
		{
			buffer[l] = 0;
			j = length;
		}
	}

	*pd = j;
}

/**
 * replace_alias - replaces an alias in the string
 * @infom: infom
 * Return: 1  or 0
 */
int replace_alias(info_t *infom)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(infom->alias, infom->argv[0], '=');
		if (!node)
			return (0);
		free(infom->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infom->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @infom: infom
 * Return: 1 or 0
 */
int replace_vars(info_t *infom)
{
	int i = 0;
	list_t *node;

	for (i = 0; infom->argv[i]; i++)
	{
		if (infom->argv[i][0] != '$' || !infom->argv[i][1])
			continue;

		if (!_strcmp(infom->argv[i], "$?"))
		{
			replace_string(&(infom->argv[i]),
				_strdup(convert_number(infom->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infom->argv[i], "$$"))
		{
			replace_string(&(infom->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infom->env, &infom->argv[i][1], '=');
		if (node)
		{
			replace_string(&(infom->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infom->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replace string
 * @oldstr: old string
 * @newStr: new string
 * Return: 1 replaced, 0 otherwise
 */
int replace_string(char **oldstr, char *newStr)
{
	free(*oldstr);
	*oldstr = newStr;
	return (1);
}
