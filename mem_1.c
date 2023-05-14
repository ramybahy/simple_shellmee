#include "shell.h"

/**
 * bfree - fes pitr NULs ades
 * @pont: ades pitr fe
 * Return: if fre 1, 0 othrws
 */
int bfree(void **pont)
{
	if (pont && *pont)
	{
		free(*pont);
		*pont = NULL;
		return (1);
	}
	return (0);
}