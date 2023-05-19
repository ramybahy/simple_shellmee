#include "shell.h"

/**
 * intracve - return true if shell intracve mode
 * @inform: strct address
 *
 * Return: if intracve mode 1, othrwse 0
 */
int intracve(info_t *inform)
{
	return (isatty(STDIN_FILENO) && inform->rdfm <= 2);
	}

/**
 * it_dlm - check if char is dlmter
 * @v: char to check
 * @dlm: the dlmter str
 * Return: 1 if true 1 , othrwse 0
 */
int it_dlm(char v, char *dlm)
{
	while (*dlm)
		if (*dlm++ == v)
			return (1);
	return (0);
}

/**
 * italph - check for alphbtc char
 * @v: char to enter
 * Return: v is alphbtc 1, othrwse 0
 */

int italph(int v)
{
	if ((v >= 'a' && v <= 'z') || (v >= 'A' && v <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _mghv - convert str to int
 * @f: str to cnvrt
 * Return: if no numbers in str 0, othrwse cnvrt num
 */

int _mghv(char *f)
{
	int j, sgn = 1, flg = 0, otpt;
	unsigned int rslt = 0;

	for (j = 0; f[j] != '\0' && flg != 2; j++)
	{
		if (f[j] == '-')
			sgn *= -1;

		if (f[j] >= '0' && f[j] <= '9')
		{
			flg = 1;
			rslt *= 10;
			rslt += (f[j] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		otpt = -rslt;
	else
		otpt = rslt;

return (otpt);
}
