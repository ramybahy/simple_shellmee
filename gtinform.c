#include "shell.h"

/**
 * clr_inform - intal info_t stct
 * @inform: strct adrs
 */
void clr_inform(info_t *inform)
{
	inform->argum = NULL;
	inform->argumv = NULL;
	inform->ph = NULL;
	inform->argumc = 0;
}

/**
 * st_inform - intal info_t strct
 * @inform: strt adrs
 * @avor: arg vctr
 */
void st_inform(info_t *inform, char **avor)
{
	int u = 0;

	inform->fnm = avor[0];
	if (inform->argum)
	{
		inform->argumv = stngtw(inform->argum, " \t");
		if (!inform->argumv)
		{
			inform->argumv = malloc(sizeof(char *) * 2);
			if (inform->argumv)
			{
				inform->argumv[0] = _stngdpl(inform->argum);
				inform->argumv[1] = NULL;
			}
		}
		for (u = 0; inform->argumv && inform->argumv[u]; u++)
			;
		inform->argumc = u;

		rplc_als(inform);
		rplc_mrs(inform);
	}
}

/**
 * fr_inform - fre info_t strct fids
 * @inform: strct adrs
 * @alez: tre fei all fds
 */
void fr_inform(info_t *inform, int alez)
{
	ffree(inform->argumv);
	inform->argumv = NULL;
	inform->ph = NULL;
	if (alez)
	{
		if (!inform->cmd_bfr)
			free(inform->argum);
		if (inform->env)
			fr_lt(&(inform->env));
		if (inform->hstr)
			fr_lt(&(inform->hstr));
		if (inform->als)
			fr_lt(&(inform->als));
		ffree(inform->environ);
			inform->environ = NULL;
		bfree((void **)inform->cmd_bfr);
		if (inform->rdfm > 2)
			close(inform->rdfm);
		_ptchr(BUF_FLUSH);
	}
}