#ifndef SH_H
# define SH_H
# define BUF 1
# include <signal.h>
//# include "../sh.h"
# include <sys/stat.h>
#include <stdio.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define INPUT_END 1
#define OUTPUT_END 0 

#define one (O_WRONLY | O_TRUNC | O_CREAT)
#define two (O_WRONLY | O_APPEND | O_CREAT)
//#define rd (O_RDONLY | O_CREAT)

FILE *fprinf_fd ;
int		g_child;

typedef struct  s_cmds
{
    char        **argv;
	t_list      *redirections;
    char        *heredoc;
    int i;
}               t_cmds;

// typedef struct  s_fd
// {
//     int     *i;
// }               t_fd;

typedef struct  s_redirection
{
    int         type;   ///1 = > /// 2 = >> /// 3 = <
	int         source_fd;
    int         source_fd1;
    int         destination_fd;
    char        *file;
    int         close;
}               t_redirection;

typedef struct  s_params
{
    int     type; 
	int     len_pipes;
    char    *key;
    char    *value;
    t_list  *environnement;
    t_list  *semicolones;
    t_list  *lst;
    int     envs;
    char    **environnement_tab;
}               t_params;

typedef struct  s_environnement
{
    char *key;
    char *value;
}               t_environnement;

typedef struct      s_dollar
{
    t_list          *env;
    int             i;
    int             i1;
    t_environnement *environnement;
    char            *dollar;
    int             d;
    char            *str;
    char            *concatenation;
    int             s;
    char            *value;
    char            *str1;
}              t_dollar;

t_list      *ft_listnew(void *content);
void		ft_lstadd1(t_list **alst, t_list *new);
void        put_tst(t_list *lst);
void		ft_lstadd2(t_list **alst, t_list *new);
void        ft_exit(t_cmds  *cmds, t_params *params);
//char        **splite_semicolon(char *read);
char        **split(char *read);
void        put_semicolones(t_list *semi);
char		**quotes_splite(char const *s, char c);
void        free2d(char **arr);
void        put_environnement(t_params *params);
void        get_environnement(t_params *params, char **env);
void        find_environnement(char *env, t_params *params);
void        add_environnement(char *key, char *value, t_params *params);
int         manage_sh(t_params *params);
char        *remove_quotes(char *string);
void		ft_lstadd3(t_list **alst, t_list *new);
t_list	    *ft_listnew(void *content);
char        *ft_add_space(char *reads);
int 	    manage_sh1(t_params *params);
void        put_tst(t_list *lst);
void        ft_initialisation(t_redirection   *redirection);
void        put_redirections(t_list *redirections);
void		change_dir(char **read, t_params *params);
void        ft_setenv(char **cmds, t_params *params);
void        ft_setenv2(t_params *para, char **nenv);

#endif