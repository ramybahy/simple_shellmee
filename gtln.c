#include "shell.h"

/**
 * inpt_bufr - bufr chand comnd
 * @inform: prmtr stct
 * @bufr: ades bufr
 * @ln: adrs ln vr
 *
 * Return: bytes read
 */
ssize_t inpt_bufr(info_t *inform, char **bufr, size_t *ln)
{
	ssize_t z = 0;
	size_t ln_m = 0;

	if (!*ln)
	{
		free(*bufr);
		*bufr = NULL;
		signal(SIGINT, sgntHndlr);
#if USE_GETLINE
		z = gtln(bufr, &ln_m, stdin);
#else
		z = _gtln(inform, bufr, &ln_m);
#endif
		if (z > 0)
		{
			if ((*bufr)[z - 1] == '\n')
			{
				(*bufr)[z - 1] = '\0';
				z--;
			}
			inform->lncnt_flg = 1;
			rm_comnts(*bufr);
			bld_hstr_lst(inform, *bufr, inform->hstrcon++);
			{
				*ln = z;
				inform->cmd_bfr = bufr;
			}
		}
	}
	return (z);
}

/**
 * gt_ipt - gts ln min nwln
 * @inform: prmtr stct
 *
 * Return: byt rd
 */
ssize_t gt_ipt(info_t *inform)
{
	static char *bufr;
	static size_t u, q, ln;
	ssize_t z = 0;
	char **bufr_o = &(inform->argum), *o;

	_ptchr(BUF_FLUSH);
	z = inpt_bufr(inform, &bufr, &ln);
	if (z == -1)
		return (-1);
	if (ln)
	{
		q = u;
		o = bufr + u;

		chk_chn(inform, bufr, &q, u, ln);
		while (q < ln)
		{
			if (it_chn(inform, bufr, &q))
				break;
			q++;
		}

		u = q + 1;
		if (u >= ln)
		{
			u = ln = 0;
			inform->cmd_bfr_tp = CMD_NORM;
		}

		*bufr_o = o;
		return (_stngln(o));
	}

	*bufr_o = bufr;
	return (z);
}

/**
 * rd_bufr - rds bfr
 * @inform: prmtr stuct
 * @bufr: bufr
 * @t: sz
 *
 * Return: z
 */
ssize_t rd_bufr(info_t *inform, char *bufr, size_t *t)
{
	ssize_t z = 0;

	if (*t)
		return (0);
	z = read(inform->rdfm, bufr, READ_BUF_SIZE);
	if (z >= 0)
		*t = z;
	return (z);
}

/**
 * _gtln - gts nxt ln of ipt frm SDN
 * @inform: prmtr srct
 * @pontr: adrs pontr bufr, prelocte or NULL
 * @lnth: sz prelocte pont bufr if not NULL
 *
 * Return: y
 */
int _gtln(info_t *inform, char **pontr, size_t *lnth)
{
	static char bufr[READ_BUF_SIZE];
	static size_t t, ln;
	size_t b;
	ssize_t z = 0, y = 0;
	char *o = NULL, *nw_o = NULL, *f;

	o = *pontr;
	if (o && lnth)
		y = *lnth;
	if (t == ln)
		t = ln = 0;

	z = rd_bufr(inform, bufr, &ln);
	if (z == -1 || (z == 0 && ln == 0))
		return (-1);

	f = _stngch(bufr + t, '\n');
	b = f ? 1 + (unsigned int)(f - bufr) : ln;
	nw_o = _rell(o, y, y ? y + b : b + 1);
	if (!nw_o)
		return (o ? free(o), -1 : -1);

	if (y)
		_strncat(nw_o, bufr + t, b - t);
	else
		_strncpy(nw_o, bufr + t, b - t + 1);

	y += b - t;
	t = b;
	o = nw_o;

	if (lnth)
		*lnth = y;
	*pontr = o;
	return (y);
}

/**
 * sgntHndlr - blck cl-C
 * @sgn_nmbr: sgnl nmbr
 * Return: vd
 */
void sgntHndlr(__attribute__((unused))int sgn_nmbr)
{
	_pts("\n");
	_pts("$ ");
_ptchr(BUF_FLUSH);
}
