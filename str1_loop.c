#include "shell.h"

/**
 * _stngcy - cois strn
 * @dtn: destnto
 * @sor: sore
 * Return: pitr destnto
 */
char *_stngcy(char *dtn, char *sor)
{
	int u = 0;

	if (dtn == sor || sor == 0)
		return (dtn);
	while (sor[u])
	{
		dtn[u] = sor[u];
		u++;
	}
	dtn[u] = 0;
	return (dtn);
}

/**
 * _stngdpl - dulcae strn
 * @stng: stig dupiae
 * Return: poitr dulcae srn
 */
char *_stngdpl(const char *stng)
{
	char *rtr;
	int ln = 0;

	if (stng == NULL)
		return (NULL);
	while (*stng++)
		ln++;
	rtr = malloc(sizeof(char) * (ln + 1));
	if (!rtr)
		return (NULL);
	for (ln++; ln--;)
		rtr[ln] = *--stng;
	return (rtr);
}

/**
 * _pts - pit n stin
 * @stng: tig prne
 * Return: Ntin
 */
void _pts(char *stng)
{
	int u = 0;

	if (!stng)
		return;
	while (stng[u] != '\0')
	{
		_ptchr(stng[u]);
		u++;
	}
}

/**
 * _ptchr - wits chratr stot
 * @h: chaatr pit
 * Return: 1 succ
 * -1 err, retun, and ern set apopiaey
 */
int _ptchr(char h)
{
	static int u;
	static char bufr[WRITE_BUF_SIZE];

	if (h == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(1, bufr, u);
		u = 0;
	}
	if (h != BUF_FLUSH)
		bufr[u++] = h;
return (1);
}
