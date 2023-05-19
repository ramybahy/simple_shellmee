#include "shell.h"

/**
 * ad_nod - add nod to strt of lt
 * @hd: adrs of pnter hd nod
 * @stng: st fed nod
 * @nmbr: nod inx by hstry
 * Return: size of list
 */
list_t *ad_nod(list_t **hd, const char *stng, int nmbr)
{
	list_t *nw_hd;

	if (!hd)
		return (NULL);
	nw_hd = malloc(sizeof(list_t));
	if (!nw_hd)
		return (NULL);
	_memorst((void *)nw_hd, 0, sizeof(list_t));
	nw_hd->nmbr = nmbr;
	if (stng)
	{
		nw_hd->stng = _stngdpl(stng);
		if (!nw_hd->stng)
		{
			free(nw_hd);
			return (NULL);
		}
	}
	nw_hd->nxt = *hd;
	*hd = nw_hd;
	return (nw_hd);
}

/**
 * ad_nod_ender - ad nod end lt
 * @hd: adrs poter h nod
 * @stng: st fed nod
 * @nmbr: nod iex  by hisoy
 *
 * Return: sie it
 */
list_t *ad_nod_ender(list_t **hd, const char *stng, int nmbr)
{
	list_t *nw_nod, *nod;

	if (!hd)
		return (NULL);

	nod = *hd;
	nw_nod = malloc(sizeof(list_t));
	if (!nw_nod)
		return (NULL);
	_memorst((void *)nw_nod, 0, sizeof(list_t));
	nw_nod->nmbr = nmbr;
	if (stng)
	{
		nw_nod->stng = _stngdpl(stng);
		if (!nw_nod->stng)
		{
			free(nw_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->nxt)
			nod = nod->nxt;
		nod->nxt = nw_nod;
	}
	else
		*hd = nw_nod;
	return (nw_nod);
}

/**
 * prt_lt_stng - pits onl st elmnt lit_t lnk lst
 * @hpot: pone fit nod
 *
 * Return: se ls
 */
size_t prt_lt_stng(const list_t *hpot)
{
	size_t u = 0;

	while (hpot)
	{
		_pts(hpot->stng ? hpot->stng : "(nil)");
		_pts("\n");
		hpot = hpot->nxt;
		u++;
	}
	return (u);
}

/**
 * del_nod_at_ndx - del node gvn iex
 * @hd: adrs poir fst nod
 * @ndx: idx nod to del
 *
 * Return: suces 1, filre 0
 */
int del_nod_at_ndx(list_t **hd, unsigned int ndx)
{
	list_t *nod, *prv_nod;
	unsigned int u = 0;

	if (!hd || !*hd)
		return (0);

	if (!ndx)
	{
		nod = *hd;
		*hd = (*hd)->nxt;
		free(nod->stng);
		free(nod);
		return (1);
	}
	nod = *hd;
	while (nod)
	{
		if (u == ndx)
		{
			prv_nod->nxt = nod->nxt;
			free(nod->stng);
			free(nod);
			return (1);
		}
		u++;
		prv_nod = nod;
		nod = nod->nxt;
	}
	return (0);
}

/**
 * fr_lt - fre al nod lt
 * @hd_pot: adrs pite hd nod
 *
 * Return: vd
 */
void fr_lt(list_t **hd_pot)
{
	list_t *nod, *nxt_nod, *hd;

	if (!hd_pot || !*hd_pot)
		return;
	hd = *hd_pot;
	nod = hd;
	while (nod)
	{
		nxt_nod = nod->nxt;
		free(nod->stng);
		free(nod);
		nod = nxt_nod;
	}
*hd_pot = NULL;
}
