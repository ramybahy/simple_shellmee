#include "shell.h"

/**
 * **stngtw - splits a string into words. Repeat delimiters are ignored
 * @stng: the input string
 * @dtg: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **stngtw(char *stng, char *dtg)
{
	char **a;
	int u, q, h, b, nmwds = 0;

	if (stng == NULL || stng[0] == 0)
		return (NULL);
	if (!dtg)
		dtg = " ";
	for (u = 0; stng[u] != '\0'; u++)
		if (!it_dlm(stng[u], dtg) && (it_dlm(stng[u + 1], dtg) || !stng[u + 1]))
			nmwds++;

	if (nmwds == 0)
		return (NULL);
	a = malloc((1 + nmwds) * sizeof(char *));
	if (!a)
		return (NULL);
	for (u = 0, q = 0; q < nmwds; q++)
	{
		while (it_dlm(stng[u], dtg))
			u++;
		h = 0;
		while (!it_dlm(stng[u + h], dtg) && stng[u + h])
			h++;
		a[q] = malloc((h + 1) * sizeof(char));
		if (!a[q])
		{
			for (h = 0; h < q; h++)
				free(a[h]);
			free(a);
			return (NULL);
		}
		for (b = 0; b < h; b++)
			a[q][b] = stng[u++];
		a[q][b] = 0;
	}
	a[q] = NULL;
	return (a);
}

/**
 * **stngtw2 - splits a string into words
 * @stng: the input string
 * @dtg: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **stngtw2(char *stng, char dtg)
{
	char **a;
	int u, q, h, b, nmwds = 0;

	if (stng == NULL || stng[0] == 0)
		return (NULL);
	for (u = 0; stng[u] != '\0'; u++)
		if ((stng[u] != dtg && stng[u + 1] == dtg) ||
				    (stng[u] != dtg && !stng[u + 1]) || stng[u + 1] == dtg)
			nmwds++;
	if (nmwds == 0)
		return (NULL);
	a = malloc((1 + nmwds) * sizeof(char *));
	if (!a)
		return (NULL);
	for (u = 0, q = 0; q < nmwds; q++)
	{
		while (stng[u] == dtg && stng[u] != dtg)
			u++;
		h = 0;
		while (stng[u + h] != dtg && stng[u + h] && stng[u + h] != dtg)
			h++;
		a[q] = malloc((h + 1) * sizeof(char));
		if (!a[q])
		{
			for (h = 0; h < q; h++)
				free(a[h]);
			free(a);
			return (NULL);
		}
		for (b = 0; b < h; b++)
			a[q][b] = stng[u++];
		a[q][b] = 0;
	}
	a[q] = NULL;
	return (a);
}