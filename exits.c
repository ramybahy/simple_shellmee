#include "shell.h"

/**
 **_strncpy - cope  stng
 *@dstn: destnton stng to be cope
 *@sorc: souc stng
 *@g: amnt of crctrs to copi
 *Return: coctnt stng
 */
char *_strncpy(char *dstn, char *sorc, int g)
{
	int u, q;
	char *a = dstn;

	u = 0;
	while (sorc[u] != '\0' && u < g - 1)
	{
		dstn[u] = sorc[u];
		u++;
	}
	if (u < g)
	{
		q = u;
		while (q < g)
		{
			dstn[q] = '\0';
			q++;
		}
	}
	return (a);
}

/**
 **_strncat - conctnt two stng
 *@dstn: frst stng
 *@sorc: nd stng
 *@g: amnt of bts to be mxmly use
 *Return: conctnt stng
 */
char *_strncat(char *dstn, char *sorc, int g)
{
	int u, q;
	char *a = dstn;

	u = 0;
	q = 0;
	while (dstn[u] != '\0')
		u++;
	while (sorc[q] != '\0' && q < g)
	{
		dstn[u] = sorc[q];
		u++;
		q++;
	}
	if (q < g)
		dstn[u] = '\0';
	return (a);
}

/**
 **_stngch - loct chrctr in stng
 *@t: stng to pars
 *@h: chrctr to look
 *Return: (t) a pontr to mem area
 */
char *_stngch(char *t, char h)
{
	do {
		if (*t == h)
			return (t);
	} while (*t++ != '\0');

return (NULL);
}
