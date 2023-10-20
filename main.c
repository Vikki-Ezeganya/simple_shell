#include "shell.h"

/**
 * main -  main
 * @acc:  count
 * @avv:  vector
 *
 * Return: 0  success, 1  error
 */
int main(int acc, char **avv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (acc == 2)
	{
		fd = open(avv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(avv[0]);
				_eputs(": 0: Can't open ");
				_eputs(avv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	_populate_env_list(info);
	read_history(info);
	hsh(info, avv);
	return (EXIT_SUCCESS);
}
