#include "shell.h"

/**
 * _myhstr - display hstr lt, start at 0.
 * @inform: Strctr contain potntal arg. Used to maint func
 *  Return: 0 Always
 */
int _myhstr(info_t *inform)
{
	prt_lt(inform->hstr);
	return (0);
}

/**
 * unst_als - set als to stng
 * @inform: prmtr struct
 * @stng: stng als
 *
 * Return: Always 0 on success, 1 on error
 */
int unst_als(info_t *inform, char *stng)
{
	int rtr;
char *k, o;
	k = _stngch(stng, '=');
	if (!k)
		return (1);
	o = *k;
	*k = 0;
	rtr = del_nod_at_ndx(&(inform->als),
	gt_nod_ndx(inform->als, nod_srts_wh(inform->als, stng, -1)));
	*k = o;
	return (rtr);
}

/**
 * st_als - sts als to stng
 * @inform: prmtr struct
 * @stng: stng als
 * Return: on success 0, on error 1
 */
int st_als(info_t *inform, char *stng)
{
	char *k;

	k = _stngch(stng, '=');
	if (!k)
		return (1);
	if (!*++k)
		return (unst_als(inform, stng));

	unst_als(inform, stng);
	return (ad_nod_ender(&(inform->als), stng, 0) == NULL);
}

/**
 * prt_als - prts an als stng
 * @nod: the als nod
 * Return: Always 0 on success, 1 on error
 */
int prt_als(list_t *nod)
{
	char *k = NULL, *r = NULL;

	if (nod)
	{
		k = _stngch(nod->stng, '=');
		for (r = nod->stng; r <= k; r++)
		_ptchr(*r);
		_ptchr('\'');
		_pts(k + 1);
		_pts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myals - mimc als bltn
 * @inform: Strtr contn potntal arg
 *  Return: 0 Always
 */
int _myals(info_t *inform)
{
	int f = 0;
	char *k = NULL;
	list_t *nod = NULL;

	if (inform->argumc == 1)
	{
		nod = inform->als;
		while (nod)
		{
			prt_als(nod);
			nod = nod->nxt;
		}
		return (0);
	}
	for (f = 1; inform->argumv[f]; f++)
	{
		k = _stngch(inform->argumv[f], '=');
		if (k)
			st_als(inform, inform->argumv[f]);
		else
		prt_als(nod_srts_wh(inform->als, inform->argumv[f], '='));
	}
	return (0);
}
