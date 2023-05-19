#include "shell.h"

/**
 * lt_ln - dtrmns leth led lst
 * @hpot: potr frt nod
 *
 * Return: sz lst
 */
size_t lt_ln(const list_t *hpot)
{
	size_t u = 0;

	while (hpot)
	{
		hpot = hpot->nxt;
		u++;
	}
	return (u);
}

/**
 * lt_to_stngs - rtus arr stig lst->sng
 * @hd: pinr frt nd
 *
 * Return: arr stig
 */
char **lt_to_stngs(list_t *hd)
{
	list_t *nod = hd;
	size_t u = lt_ln(hd), q;
	char **stngs;
	char *stng;

	if (!hd || !u)
		return (NULL);
	stngs = malloc(sizeof(char *) * (u + 1));
	if (!stngs)
		return (NULL);
	for (u = 0; nod; nod = nod->nxt, u++)
	{
		stng = malloc(_stngln(nod->stng) + 1);
		if (!stng)
		{
			for (q = 0; q < u; q++)
				free(stngs[q]);
			free(stngs);
			return (NULL);
		}

		stng = _stngcy(stng, nod->stng);
		stngs[u] = stng;
	}
	stngs[u] = NULL;
	return (stngs);
}


/**
 * prt_lt - prnt al elmnts lst_t link lst
 * @hpot: pontr frt nod
 *
 * Return: sz of lt
 */
size_t prt_lt(const list_t *hpot)
{
	size_t u = 0;

	while (hpot)
	{
		_pts(cnvrt_num(hpot->nmbr, 10, 0));
		_ptchr(':');
		_ptchr(' ');
		_pts(hpot->stng ? hpot->stng : "(nil)");
		_pts("\n");
		hpot = hpot->nxt;
		u++;
	}
	return (u);
}

/**
 * nod_srts_wh - rtus nod whe stg stts wh pfi
 * @nod: ponr lst hd
 * @prfx: strg mtc
 * @chr: chrctr prfx mtc
 *
 * Return: mch nod o nul
 */
list_t *nod_srts_wh(list_t *nod, char *prfx, char chr)
{
	char *o = NULL;

	while (nod)
	{
		o = srts_wh(nod->stng, prfx);
		if (o && ((chr == -1) || (*o == chr)))
			return (nod);
		nod = nod->nxt;
	}
	return (NULL);
}

/**
 * gt_nod_ndx - idx nod
 * @hd: pntr lt hd
 * @nod: pontr nod
 *
 * Return: idx nod r -1
 */
ssize_t gt_nod_ndx(list_t *hd, list_t *nod)
{
	size_t u = 0;

	while (hd)
	{
		if (hd == nod)
			return (u);
		hd = hd->nxt;
		u++;
	}
return (-1);
}
