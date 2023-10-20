#include "shell.h"

/**
 * input_buf - input_buf
 * @infom: infom
 * @buff: address of buffer
 * @length: address of len var
 * Return: bytes
 */
ssize_t input_buf(info_t *infom, char **buff, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = _getline(infom, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			infom->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(infom, *buff, infom->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = r;
				infom->cmd_buf = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - get_input
 * @infom: infom
 * Return: bytes
 */
ssize_t get_input(info_t *infom)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(infom->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(infom, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(infom, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(infom, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			infom->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @infom: infom
 * @buff: buff
 * @size: size
 * Return: r
 */
ssize_t read_buf(info_t *infom, char *buff, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(infom->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @infom: parameter struct
 * @pt: pt
 * @length: length
 * Return: s
 */
int _getline(info_t *infom, char **pt, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pt;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(infom, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*pt = p;
	return (s);
}

/**
 * sigintHandler - sigintHandler
 * @sig_numb: sig_numb
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
