#include "shell.h"

/**
 *_ept - prts inpt stng
 * @stng: stng  be prnt
 *
 * Return: Notng
 */
void _ept(char *stng)
{
	int j = 0;

	if (!stng)
		return;
	while (stng[j] != '\0')
	{
		_eptchr(stng[j]);
		j++;
	}
}

/**
 * _eptchr - wrt chrctr d to stdrr
 * @d: chrctr to prnt
 * Return: On sucss 1.
 * On error, -1 is rtrn, errno is set appr
 */
int _eptchr(char d)
{
	static int j;
	static char bufr[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, bufr, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		bufr[j++] = d;
	return (1);
}

/**
 * _ptfm - wrt chara d to given fm
 * @d: chrctr to prnt
 * @fm: The fildscrptr to wrt
 * Return: On success 1.
 * On error, -1 is rtrn, errno is set appr
 */
int _ptfm(char d, int fm)
{
	static int j;
	static char bufr[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fm, bufr, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		bufr[j++] = d;
	return (1);
}

/**
 *_ptsfm - prnt inpt stng
 * @stng: stng to pnte
 * @fm: fildecrptr to wrt
 *
 * Return: num of chrs put
 */
int _ptsfm(char *stng, int fm)
{
	int j = 0;

	if (!stng)
		return (0);
	while (*stng)
	{
		j += _ptfm(*stng++, fm);
	}
return (j);
}
