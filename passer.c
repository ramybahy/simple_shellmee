#include "shell.h"

/**
 * et_cmd - determines if a file is an executable command
 * @inform: the info struct
 * @ph: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int et_cmd(info_t *inform, char *ph)
{
	struct stat st;

	(void)inform;
	if (!ph || stat(ph, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dpl_chrts - duplicates characters
 * @phstng: the PATH string
 * @srt: starting index
 * @sop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dpl_chrts(char *phstng, int srt, int sop)
{
	static char bufr[1024];
	int u = 0, h = 0;

	for (h = 0, u = srt; u < sop; u++)
		if (phstng[u] != ':')
			bufr[h++] = phstng[u];
	bufr[h] = 0;
	return (bufr);
}

/**
 * fn_ph - finds this cmd in the PATH string
 * @inform: the info struct
 * @phstng: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *fn_ph(info_t *inform, char *phstng, char *cmd)
{
	int u = 0, curt_ps = 0;
	char *ph;

	if (!phstng)
		return (NULL);
	if ((_stngln(cmd) > 2) && srts_wh(cmd, "./"))
	{
		if (et_cmd(inform, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!phstng[u] || phstng[u] == ':')
		{
			ph = dpl_chrts(phstng, curt_ps, u);
			if (!*ph)
				_stngct(ph, cmd);
			else
			{
				_stngct(ph, "/");
				_stngct(ph, cmd);
			}
			if (et_cmd(inform, ph))
				return (ph);
			if (!phstng[u])
				break;
			curt_ps = u;
		}
		u++;
	}
return (NULL);
}
