#include "shell.h"

/**
 * _errmghv - covrt stng to int
 * @n: stng to be covrtd
 * Return: 0 if no nub in stng, convrd numb othwe
 *       -1 on err
 */
int _errmghv(char *n)
{
	int j = 0;
	unsigned long int rslt = 0;

	if (*n == '+')
		n++;  /* TODO: wh do ths mak man rtrn 255? */
	for (j = 0;  n[j] != '\0'; j++)
	{
		if (n[j] >= '0' && n[j] <= '9')
		{
			rslt *= 10;
			rslt += (n[j] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * prt_err - pnts an err mesag
 * @inform: prmtr & rtrn inf stct
 * @estng: stng contn specfe err tp
 * Return: 0 if no nubers in stng, convrt nuber othrws
 *        -1 on err
 */
void prt_err(info_t *inform, char *estng)
{
	_ept(inform->fnm);
	_ept(": ");
	prt_o(inform->ln_cnt, STDERR_FILENO);
	_ept(": ");
	_ept(inform->argumv[0]);
	_ept(": ");
	_ept(estng);
}

/**
 * prt_o - func prnt a decml (intgr) numer (bs 10)
 * @inpt: inpt
 * @fm: the fildscrptr to wrt
 *
 * Return: numer of chrct prnt
 */
int prt_o(int inpt, int fm)
{
	int (*__ptchr)(char) = _ptchr;
	int j, cnt = 0;
	unsigned int _abs_, crnt;

	if (fm == STDERR_FILENO)
		__ptchr = _eptchr;
	if (inpt < 0)
	{
		_abs_ = -inpt;
		__ptchr('-');
		cnt++;
	}
	else
		_abs_ = inpt;
	crnt = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__ptchr('0' + crnt / j);
			cnt++;
		}
		crnt %= j;
	}
	__ptchr('0' + crnt);
	cnt++;

	return (cnt);
}

/**
 * cnvrt_num - convrtr func, a clon of ita
 * @nmbr: nuber
 * @bs: bs
 * @flg: arg flg
 *
 * Return: stng
 */
char *cnvrt_num(long int nmbr, int bs, int flg)
{
	static char *arr;
	static char bufr[50];
	char sgn = 0;
	char *pontr;
	unsigned long x = nmbr;

	if (!(flg & CONVERT_UNSIGNED) && nmbr < 0)
	{
		x = -nmbr;
		sgn = '-';

	}
	arr = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pontr = &bufr[49];
	*pontr = '\0';

	do	{
		*--pontr = arr[x % bs];
		x /= bs;
	} while (x != 0);

	if (sgn)
		*--pontr = sgn;
	return (pontr);
}

/**
 * rm_comnts - func rplcs fst instnc of '#' wh '\0'
 * @bufr: adss of stng to modf
 * Return: 0 Always
 */
void rm_comnts(char *bufr)
{
	int j;

	for (j = 0; bufr[j] != '\0'; j++)
		if (bufr[j] == '#' && (!j || bufr[j - 1] == ' '))
		{
			bufr[j] = '\0';
			break;
		}
}