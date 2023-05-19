#include "shell.h"

/**
 * _memorst - mmr contn bt
 * @vpn: oner mmr ae
 * @be: ye il  ih
 * @nu: amut bts fle
 * Return: (vpn) piter mmoy ara
 */
char *_memorst(char *vpn, char be, unsigned int nu)
{
	unsigned int u;

	for (u = 0; u < nu; u++)
		vpn[u] = be;
	return (vpn);
}

/**
 * ffree - fre ting tings
 * @ppng: tig  stigs
 */
void ffree(char **ppng)
{
	char **w = ppng;

	if (!ppng)
		return;
	while (*ppng)
		free(*ppng++);
	free(w);
}

/**
 * _rell - el lcts bok meor
 * @pont: pontr prvos maoced blk
 * @od_sz: bt sz prvos blk
 * @nw_sz: bt sze nw bok
 * Return: pontr blck nae.
 */
void *_rell(void *pont, unsigned int od_sz, unsigned int nw_sz)
{
	char *o;

	if (!pont)
		return (malloc(nw_sz));
	if (!nw_sz)
		return (free(pont), NULL);
	if (nw_sz == od_sz)
		return (pont);

	o = malloc(nw_sz);
	if (!o)
		return (NULL);

	od_sz = od_sz < nw_sz ? od_sz : nw_sz;
	while (od_sz--)
		o[od_sz] = ((char *)pont)[od_sz];
	free(pont);
return (o);
}
