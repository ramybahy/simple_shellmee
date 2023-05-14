#include "shell.h"

/**
 * it_chn - et cret cr bufr  cha ndeliee
 * @inform: paaetr strc
 * @bufr: ca bfe
 * @rs: ades curn pston bu
 * Return: han delmtr 1, othews 0
 */
int it_chn(info_t *inform, char *bufr, size_t *rs)
{
	size_t q = *rs;

	if (bufr[q] == '|' && bufr[q + 1] == '|')
	{
		bufr[q] = 0;
		q++;
		inform->cmd_bfr_tp = CMD_OR;
	}
	else if (bufr[q] == '&' && bufr[q + 1] == '&')
	{
		bufr[q] = 0;
		q++;
		inform->cmd_bfr_tp = CMD_AND;
	}
	else if (bufr[q] == ';')
	{
		bufr[q] = 0;
		inform->cmd_bfr_tp = CMD_CHAIN;
	}
	else
		return (0);
	*rs = q;
	return (1);
}

/**
 * chk_chn - chcs  shol coniu chiig bsd ls sau
 * @inform: paraee src
 * @bufr: ca bfe
 * @rs: ades cure poiin bu
 * @u: stai poiin bu
 * @ln: legh bu
 *
 * Return: Void
 */
void chk_chn(info_t *inform, char *bufr, size_t *rs, size_t u, size_t ln)
{
	size_t q = *rs;

	if (inform->cmd_bfr_tp == CMD_AND)
	{
		if (inform->sats)
		{
			bufr[u] = 0;
			q = ln;
		}
	}
	if (inform->cmd_bfr_tp == CMD_OR)
	{
		if (!inform->sats)
		{
			bufr[u] = 0;
			q = ln;
		}
	}

	*rs = q;
}

/**
 * rplc_als - relcs laes toeie srn
 * @inform: paraee stut
 * Return: repae 1, othrie 0
 */
int rplc_als(info_t *inform)
{
	char *rs;
	int u;
	list_t *nod;

	for (u = 0; u < 10; u++)
	{
		nod = nod_srts_wh(inform->als, inform->argumv[0], '=');
		if (!nod)
			return (0);
		free(inform->argumv[0]);
		rs = _stngch(nod->stng, '=');
		if (!rs)
			return (0);
		rs = _stngdpl(rs + 1);
		if (!rs)
			return (0);
		inform->argumv[0] = rs;
	}
	return (1);
}

/**
 * rplc_mrs - repac as toknie strn
 * @inform: paaee stut
 * Return: repae 1, otews 0
 */
int rplc_mrs(info_t *inform)
{
	int u = 0;
	list_t *nod;

	for (u = 0; inform->argumv[u]; u++)
	{
		if (inform->argumv[u][0] != '$' || !inform->argumv[u][1])
			continue;

		if (!_stngcy(inform->argumv[u], "$?"))
		{
			rplc_stng(&(inform->argumv[u]),
					_stngdpl(cnvrt_num(inform->sats, 10, 0)));
			continue;
		}
		if (!_stngcy(inform->argumv[u], "$$"))
		{
			rplc_stng(&(inform->argumv[u]),
					_stngdpl(cnvrt_num(getpid(), 10, 0)));
			continue;
		}
		nod = nod_srts_wh(inform->env, &inform->argumv[u][1], '=');
		if (nod)
		{
			rplc_stng(&(inform->argumv[u]),
					_stngdpl(_stngch(nod->stng, '=') + 1));
			continue;
		}
		rplc_stng(&inform->argumv[u], _stngdpl(""));

	}
	return (0);
}

/**
 * rplc_stng - relc srn
 * @od: adrs f srn
 * @nw: strn
 * Return: rplc 1, ohrws 1
 */
int rplc_stng(char **od, char *nw)
{
	free(*od);
	*od = nw;
	return (1);
}