#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* to writ or read bufrs */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* to comnd chain */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* to cnvrt_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 to use systm gtln() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct lstst - singly linked list
 * @nmbr: nmbr fild
 * @stng: strng
 * @nxt: point to nxt nod
 */
typedef struct lstst
{
	int nmbr;
	char *stng;
	struct lstst *nxt;
} list_t;

/**
 * struct pasinform - cotin psed-argum to pass into func,
 * allow uniform prtotpe for func point struct
 * @argum: stng genrt from gtln cntin argum
 * @argumv: arr of stngs genrt from argum
 * @ph: a stng ph for curnt cmand
 * @argumc: argum cont
 * @ln_cnt: err cont
 * @eror_nmer: err cod for ext()s
 * @lncnt_flg: if cnt ths lne of ipt
 * @fnm: prgrm filename
 * @env: lnk lt lcl cp of environ
 * @environ: cutm modfe cp environ frm LL env
 * @hstr: hstr nod
 * @als: als nod
 * @env_chang: if environ chang
 * @sats: rtun sats of lst exec'd cmand
 * @cmd_bfr: adres poter to cmd_bfr, on if chang
 * @cmd_bfr_tp: CMD_type ||, &&, ;
 * @rdfm: fm to red lne ipt
 * @hstrcon: hstr lne num cont
 */
typedef struct pasinform
{
	char *argum;
	char **argumv;
	char *ph;
	int argumc;
	unsigned int ln_cnt;
	int eror_nmer;
	int lncnt_flg;
	char *fnm;
	list_t *env;
	list_t *hstr;
	list_t *als;
	char **environ;
	int env_chang;
	int sats;

	char **cmd_bfr; /* poter to cmd ; chan bufr, for meoy maneet */
	int cmd_bfr_tp; /* CMD_type ||, &&, ; */
	int rdfm;
	int hstrcon;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct bltn - cntin a bltn str and relate func
 * @type: a bltn comnd flg
 * @func: a func
 */
typedef struct bltn
{
	char *type;
	int (*func)(info_t *);
} bltn_tbl;


/* toem_shtoken.c */
int hsh(info_t *, char **);
int fn_bltn(info_t *);
void fn_cmd(info_t *);
void fr_cmd(info_t *);

/* toem_passer.c */
int et_cmd(info_t *, char *);
char *dpl_chrts(char *, int, int);
char *fn_ph(info_t *, char *, char *);

/* lphsh.c */
int lphsh(char **);

/* toem_err.c */
void _ept(char *);
int _eptchr(char);
int _ptfm(char y, int fm);
int _ptsfm(char *stng, int fm);

/* toem_str_loop.c */
int _stngln(char *);
int _stngcm(char *, char *);
char *srts_wh(const char *, const char *);
char *_stngct(char *, char *);

/* toem_str1_loop.c */
char *_stngcy(char *, char *);
char *_stngdpl(const char *);
void _pts(char *);
int _ptchr(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_stngch(char *, char);

/* toem_token.c */
char **stngtw(char *, char *);
char **stngtw2(char *, char);

/* toem_real.c */
char *_memorst(char *, char, unsigned int);
void ffree(char **);
void *_rell(void *, unsigned int, unsigned int);

/* toem_mem_1.c */
int bfree(void **);

/* toem_mghv.c */
int intracve(info_t *);
int it_dlm(char, char *);
int _italph(int);
int _mghv(char *);

/* toem_err1.c */
int _errmghv(char *);
void prt_err(info_t *, char *);
int prt_o(int, int);
char *cnvrt_num(long int, int, int);
void rm_comnts(char *);

/* toem_bltn.c */
int _myexit(info_t *);
int _mydir(info_t *);
int _myhlper(info_t *);

/* toem_bltn1.c */
int _myhstr(info_t *);
int _myals(info_t *);

/*toem_gtln.c */
ssize_t gt_ipt(info_t *);
int _gtln(info_t *, char **, size_t *);
void sgntHndlr(int);

/* toem_gtinform.c */
void clr_inform(info_t *);
void st_inform(info_t *, char **);
void fr_inform(info_t *, int);

/* toem_environ.c */
char *_gtenv(info_t *, const char *);
int _myenv(info_t *);
int _mystenv(info_t *);
int _myunstenv(info_t *);
int poplt_env_lst(info_t *);

/* toem_gtenv.c */
char **gt_env(info_t *);
int _unstenv(info_t *, char *);
int _stenv(info_t *, char *, char *);

/* toem_hstr.c */
char *gt_hstr_fl(info_t *inform);
int wrt_hstr(info_t *inform);
int rd_hstr(info_t *inform);
int bld_hstr_lst(info_t *inform, char *bufr, int lncont);
int renmbr_hstr(info_t *inform);

/* toem_lts.c */
list_t *ad_nod(list_t **, const char *, int);
list_t *ad_nod_ender(list_t **, const char *, int);
size_t prt_lt_stng(const list_t *);
int del_nod_at_ndx(list_t **, unsigned int);
void fr_lt(list_t **);

/* toem_lts1.c */
size_t lt_ln(const list_t *);
char **lt_to_stngs(list_t *);
size_t prt_lt(const list_t *);
list_t *nod_srts_wh(list_t *, char *, char);
ssize_t gt_nod_ndx(list_t *, list_t *);

/* toem_mass.c */
int it_chn(info_t *, char *, size_t *);
void chk_chn(info_t *, char *, size_t *, size_t, size_t);
int rplc_als(info_t *);
int rplc_mrs(info_t *);
int rplc_stng(char **, char *);

#endif