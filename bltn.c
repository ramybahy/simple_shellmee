#include "shell.h"

/**
 * _myexit - exit shel
 * @inform: Strctr contin ptntal arg Use to mintin
 * Return: ext stats
 * if info (0), argumv[0] != "exit"
 */
int _myexit(info_t *inform)
{
	int extchc;

	if (inform->argumv[1]) /* If ther ext arg */
	{
		extchc = _errmghv(inform->argumv[1]);
		if (extchc == -1)
		{
			inform->sats = 2;
			prt_err(inform, "Illegal number: ");
			_ept(inform->argumv[1]);
			_eptchr('\n');
			return (1);
		}
		inform->eror_nmer = _errmghv(inform->argumv[1]);
		return (-2);
	}
	inform->eror_nmer = -1;
	return (-2);
}

/**
 * _mydir - change curnt dirct
 * @inform: Strctur contin potntal arg to mintin
 * cnstnt func prtotpe.
 * Return: 0 Always
 */
int _mydir(info_t *inform)
{
	char *r, *direct, bufr[1024];
	int chdir_retr;

	r = getcwd(bufr, 1024);
	if (!r)
		_pts("TODO: >>gtcd failr emsg hre<<\n");
	if (!inform->argumv[1])
	{
		direct = _gtenv(inform, "HOME=");
		if (!direct)
			chdir_retr = chdir((direct = _gtenv(inform, "PWD=")) ? direct : "/");
		else
			chdir_retr = chdir(direct);
	}
	else if (strcmp(inform->argumv[1], "-") == 0)
	{
		if (!_gtenv(inform, "OLDPWD="))
		{
			_pts(r);
			_ptchr('\n');
			return (1);
		}
		_pts(_gtenv(inform, "OLDPWD=")), _ptchr('\n');
		chdir_retr = chdir((direct = _gtenv(inform, "OLDPWD=")) ? direct : "/");
	}
	else
		chdir_retr = chdir(inform->argumv[1]);
	if (chdir_retr == -1)
	{
		prt_err(inform, "can't cd to ");
		_ept(inform->argumv[1]), _eptchr('\n');
	}
	else
	{
		_stenv(inform, "OLDPWD", _gtenv(inform, "PWD="));
		_stenv(inform, "PWD", getcwd(bufr, 1024));
	}
	return (0);
}
/**
 * _myhlper - chng curnt direc of t
 * @inform: Strctr contain potntal arg
 * Return: 0 Always
 */
int _myhlper(info_t *inform)
{
	char **argum_arr;
	argum_arr = inform->argumv;

	_pts("help call work, Func not yet implemt \n");
	if (0)
		_pts(*argum_arr);
	return (0);
}