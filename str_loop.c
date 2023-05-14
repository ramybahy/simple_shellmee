#include "shell.h"

/**
 * _stngln - reurs lnt srn
 * @stng: sti hs lnt chc
 * Return: intgr lgh srn
 */
int _stngln(char *stng)
{
	int u = 0;

	if (!stng)
		return (0);

	while (*stng++)
		u++;
	return (u);
}

/**
 * _stngcm - prors lxcgapi coprsn strns
 * @stng1: is srn
 * @stng2: seod srn
 * return: etv ift<s2 psiiv  t  zos  t _stngcm
 */

int _stngcm(char *stng1, char *stng2)
{
	while (*stng1 && *stng2)
	{
		if (*stng1 != *stng2)
			return (*stng1 - *stng2);
		stng1++;
		stng2++;
	}
	if (*stng1 == *stng2)
		return (0);
	else
		return (*stng1 < *stng2 ? -1 : 1);
}

/**
 * srts_wh - chcs nel str wt hytc
 * @hystk: stig sac
 * @ndl: ubtig fn
 * Return: ades e chr hasak NL
 */
char *srts_wh(const char *hystk, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hystk++)
			return (NULL);
	return ((char *)hystk);
}

/**
 * _stngct - conaeats stig
 * @dtn: detiain bfe
 * @sor: suc bfe
 * Return: pitr detnain bufr
 */
char *_stngct(char *dtn, char *sor)
{
	char *rtr = dtn;

	while (*dtn)
		dtn++;
	while (*sor)
		*dtn++ = *sor++;
	*dtn = *sor;
	return (rtr);
}