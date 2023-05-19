#include "shell.h"

/**
 * gt_hstr_fl - gt hisry fil
 * @inform: prmtr srct
 * Return: alctd stng cona hsto fle
 */

char *gt_hstr_fl(info_t *inform)
{
	char *bufr, *direct;

	direct = _gtenv(inform, "HOME=");
	if (!direct)
		return (NULL);
	bufr = malloc(sizeof(char) * (_stngln(direct) + _stngln(HIST_FILE) + 2));
	if (!bufr)
		return (NULL);
	bufr[0] = 0;
	_stngcy(bufr, direct);
	_stngct(bufr, "/");
	_stngct(bufr, HIST_FILE);
	return (bufr);
}

/**
 * wrt_hstr - crats fl, apns exst fe
 * @inform: prmetr stct
 * Return: on success 1, else -1
 */
int wrt_hstr(info_t *inform)
{
	ssize_t fm;
	char *flnam = gt_hstr_fl(inform);
	list_t *nod = NULL;

	if (!flnam)
		return (-1);

	fm = open(flnam, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(flnam);
	if (fm == -1)
		return (-1);
	for (nod = inform->hstr; nod; nod = nod->nxt)
	{
		_ptsfm(nod->stng, fm);
		_ptfm('\n', fm);
	}
	_ptfm(BUF_FLUSH, fm);
	close(fm);
	return (1);
}

/**
 * rd_hstr - rds hstry frm fil
 * @inform: prmetr stuct
 *
 * Return: on success hstrcon, ohrws 0
 */
int rd_hstr(info_t *inform)
{
	int u, las = 0, lncont = 0;
	ssize_t fm, rdln, fsz = 0;
	struct stat st;
	char *bufr = NULL, *flnam = gt_hstr_fl(inform);

	if (!flnam)
		return (0);

	fm = open(flnam, O_RDONLY);
	free(flnam);
	if (fm == -1)
		return (0);
	if (!fstat(fm, &st))
		fsz = st.st_size;
	if (fsz < 2)
		return (0);
	bufr = malloc(sizeof(char) * (fsz + 1));
	if (!bufr)
		return (0);
	rdln = read(fm, bufr, fsz);
	bufr[fsz] = 0;
	if (rdln <= 0)
		return (free(bufr), 0);
	close(fm);
	for (u = 0; u < fsz; u++)
		if (bufr[u] == '\n')
		{
			bufr[u] = 0;
			bld_hstr_lst(inform, bufr + las, lncont++);
			las = u + 1;
		}
	if (las != u)
		bld_hstr_lst(inform, bufr + las, lncont++);
	free(bufr);
	inform->hstrcon = lncont;
	while (inform->hstrcon-- >= HIST_MAX)
		del_nod_at_ndx(&(inform->hstr), 0);
	renmbr_hstr(inform);
	return (inform->hstrcon);
}

/**
 * bld_hstr_lst - ad enry hstr lnk lst
 * @inform: Strctr cotan potntl arg Use mantn
 * @bufr: bufr
 * @lncont: hstr lnecont, hstrcon
 *
 * Return: 0 Always
 */
int bld_hstr_lst(info_t *inform, char *bufr, int lncont)
{
	list_t *nod = NULL;

	if (inform->hstr)
		nod = inform->hstr;
	ad_nod_ender(&nod, bufr, lncont);

	if (!inform->hstr)
		inform->hstr = nod;
	return (0);
}

/**
 * renmbr_hstr - renbrs hstr lnk lst aftr chang
 * @inform: Strctr cotin potntl arg Use mantn
 * Return: nw hstrcon
 */
int renmbr_hstr(info_t *inform)
{
	list_t *nod = inform->hstr;
	int u = 0;

	while (nod)
	{
		nod->nmbr = u++;
		nod = nod->nxt;
	}
return (inform->hstrcon = u);
}
