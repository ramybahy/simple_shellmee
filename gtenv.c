#include "shell.h"

/**
 * gt_env - rtun stng arr cp of eni
 * @inform: Strctr cotin ptnil arg
 * Return: 0 Always
 */
char **gt_env(info_t *inform)
{
	if (!inform->environ || inform->env_chang)
	{
		inform->environ = lt_to_stngs(inform->env);
		inform->env_chang = 0;
	}

	return (inform->environ);
}

/**
 * _unstenv - Rem eniomnt var
 * @inform: Strctr contin ptntal arg
 *  Return: on delete 1, otherwise 0
 * @var: stng env vr proe
 */
int _unstenv(info_t *inform, char *var)
{
	list_t *nod = inform->env;
	size_t u = 0;
	char *o;

	if (!nod || !var)
		return (0);

	while (nod)
	{
		o = srts_wh(nod->stng, var);
		if (o && *o == '=')
		{
			inform->env_chang = del_nod_at_ndx(&(inform->env), u);
			u = 0;
			nod = inform->env;
			continue;
		}
		nod = nod->nxt;
		u++;
	}
	return (inform->env_chang);
}

/**
 * _stenv - Intal  nw enronm vr
 * @inform: Strctr cntin ptntal arg
 * @var: stng env vr prpr
 * @val: sng env vr val
 *  Return:  0 Always
 */
int _stenv(info_t *inform, char *var, char *val)
{
	char *bufr = NULL;
	list_t *nod;
	char *o;

	if (!var || !val)
		return (0);

	bufr = malloc(_stngln(var) + _stngln(val) + 2);
	if (!bufr)
		return (1);
	_stngcy(bufr, var);
	_stngct(bufr, "=");
	_stngct(bufr, val);
	nod = inform->env;
	while (nod)
	{
		o = srts_wh(nod->stng, var);
		if (o && *o == '=')
		{
			free(nod->stng);
			nod->stng = bufr;
			inform->env_chang = 1;
			return (0);
		}
		nod = nod->nxt;
	}
	ad_nod_ender(&(inform->env), bufr, 0);
	free(bufr);
	inform->env_chang = 1;
	return (0);
}