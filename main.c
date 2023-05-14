#include "shell.h"

/**
 * main - enr pit
 * @acnt: argum cot
 * @avor: argum vetr
 * Return: suces 0, err 1
 */

int main(int acnt, char **avor)
{
	info_t inform[] = { INFO_INIT };
	int fm = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fm)
			: "r" (fm));

	if (acnt == 2)
	{
		fm = open(avor[1], O_RDONLY);
		if (fm == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_pts(avor[0]);
				_pts(": 0: Can't open ");
				_pts(avor[1]);
				_eptchr('\n');
				_eptchr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inform->rdfm = fm;
	}
	poplt_env_lst(inform);
	rd_hstr(inform);
	hsh(inform, avor);
	return (EXIT_SUCCESS);
}