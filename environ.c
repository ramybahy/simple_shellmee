#include "shell.h"

/**
 * _myenv - prts curnt envir
 * @inform: Strutr contain potntal argu. Used to maintain
 * Return: 0 Always
 */
int _myenv(info_t *inform)
{
	prt_lt_stng(inform->env);
	return (0);
}

/**
 * _gtenv - gets value environ var
 * @inform: Strctr contin potntal arg
 * @nm: env var nm
 *
 * Return: the value
 */
char *_gtenv(info_t *inform, const char *nm)
{
	list_t *nod = inform->env;
	char *b;

	while (nod)
	{
		b = srts_wh(nod->stng, nm);
		if (b && *b)
			return (b);
		nod = nod->nxt;
	}
	return (NULL);
}

/**
 * _mystenv - Intal new environt var
 * @inform: Strctr contain potntl arg
 *  Return: 0 Always
 */
int _mystenv(info_t *inform)
{
	if (inform->argumc != 3)
	{
		_pts("Incorrect number of arguements\n");
		return (1);
	}
	if (_stenv(inform, inform->argumv[1], inform->argumv[2]))
		return (0);
	return (1);
}

/**
 * _myunstenv - Remv enviro var
 * @inform: Strctr cntain potntal arg
 * Return: 0 Always
 */
int _myunstenv(info_t *inform)
{
	int j;

	if (inform->argumc == 1)
	{
		_pts("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= inform->argumc; j++)
		_unstenv(inform, inform->argumv[j]);

	return (0);
}

/**
 * poplt_env_lst - poplt env link lst
 * @inform: Strctr contain potntal arg
 * Return: 0 Always
 */
int poplt_env_lst(info_t *inform)
{
	list_t *nod = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		ad_nod_ender(&nod, environ[j], 0);
	inform->env = nod;
	return (0);
}