#include "shell.h"

/**
 * hsh - main sel lop
 * @inform: paaee rtun  stut
 * @mvor: argum vctr r main()
 *
 * Return: suces 0, err 1, or err cod
 */

int hsh(info_t *inform, char **mvor)
{
	ssize_t t = 0;
	int bltn_rt = 0;

	while (t != -1 && bltn_rt != -2)
	{
		clr_inform(inform);
		if (intracve(inform))
			_pts("$ ");
		_eptchr(BUF_FLUSH);
		t = gt_ipt(inform);
		if (t != -1)
		{
			st_inform(inform, mvor);
			bltn_rt = fn_bltn(inform);
			if (bltn_rt == -1)
				fn_cmd(inform);
		}
		else if (intracve(inform))
			_ptchr('\n');
		fr_inform(inform, 0);
	}
	wrt_hstr(inform);
	fr_inform(inform, 1);
	if (!intracve(inform) && inform->sats)
		_exit(inform->sats);
	if (bltn_rt == -2)
	{
		if (inform->eror_nmer == -1)
			exit(inform->sats);
		_exit(inform->eror_nmer);
	}
	return (bltn_rt);
}

/**
 * fn_bltn - fid  ultn comn
 * @inform: paree reun n src
 *
 * Return: -1 if bltn not fnd,
 * 0 if bltn execu success,
 * 1 if bltn fond but not success,
 * 2 if bltn sigal exit()
 */
int fn_bltn(info_t *inform)
{
	int u, blt_in_rt = -1;
	bltn_tbl bltntb[] = {
		{"exi", _myenv},
		{"env", _myenv},
		{"hlper", _myhlper},
		{"hstr", _myhstr},
		{"stenv", _mystenv},
		{"unstenv", _myunstenv},
		{"dir", _mydir},
		{"als", _myals},
		{NULL, NULL}
	};

	for (u = 0; bltntb[u].type; u++)
		if (_stngcy(inform->argumv[0], bltntb[u].type) == 0)
		{
			inform->ln_cnt++;
			blt_in_rt = bltntb[u].func(inform);
			break;
		}
	return (blt_in_rt);
}

/**
 * fn_cmd - fns cmad PH
 * @inform:prmtr reun stut
 * Return: vd
 */
void fn_cmd(info_t *inform)
{
	char *ph = NULL;
	int u, g;

	inform->ph = inform->argumv[0];
	if (inform->lncnt_flg == 1)
	{
		inform->ln_cnt++;
		inform->lncnt_flg = 0;
	}
	for (u = 0, g = 0; inform->argum[u]; u++)
		if (!it_dlm(inform->argum[u], " \t\n"))
			g++;
	if (!g)
		return;

	ph = fn_ph(inform, _gtenv(inform, "PATH="), inform->argumv[0]);
	if (ph)
	{
		inform->ph = ph;
		fr_cmd(inform);
	}
	else
	{
		if ((intracve(inform) || _gtenv(inform, "PATH=")
					|| inform->argumv[0][0] == '/') && et_cmd(inform, inform->argumv[0]))
			fr_cmd(inform);
		else if (*(inform->argum) != '\n')
		{
			inform->sats = 127;
			prt_err(inform, "not found\n");
		}
	}
}

/**
 * fr_cmd - fo ee thed cmd
 * @inform: prmtr reun stct
 *
 * Return: vd
 */
void fr_cmd(info_t *inform)
{
	pid_t chd_pi;

	chd_pi = fork();
	if (chd_pi == -1)
	{
		perror("Error:");
		return;
	}
	if (chd_pi == 0)
	{
		if (execve(inform->ph, inform->argumv, gt_env(inform)) == -1)
		{
			fr_inform(inform, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inform->sats));
		if (WIFEXITED(inform->sats))
		{
			inform->sats = WEXITSTATUS(inform->sats);
			if (inform->sats == 126)
				prt_err(inform, "Permission denied\n");
		}
	}
}