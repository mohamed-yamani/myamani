#include "sh.h"

void    ft_env(t_params *params)
{
	t_list          *environnement;
	t_environnement *env;

	environnement = params->environnement;
	while (environnement)
	{
		env = environnement->content;
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		environnement = environnement->next;
	}
}

void    ft_setenv(char **cmds, t_params *params)
{
	if (cmds[3])
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		free2d(cmds);
		return ;
	}
	add_environnement(cmds[1], cmds[2],  params); 
}

void    ft_unsetenv(char **cmds, t_params *params)
{
	t_list          *environnement;
	t_list          *tmp;
	t_environnement *env;
	t_environnement *next_env;

	environnement = params->environnement;
	env = environnement->content;
	if (!ft_strcmp(env->key, cmds[1]))
	{
		environnement = environnement->next;
		params->environnement = environnement;
		return;
	}
	while (environnement)
	{
		env = environnement->content;
		if (environnement->next)
			next_env = environnement->next->content;
		if (!ft_strcmp(next_env->key, cmds[1]))
		{
			tmp = environnement->next;
			environnement->next = environnement->next->next;
			free(tmp);
		}
		environnement = environnement->next;
	}
}

void    ft_echo(char **arr)
{ 
	int i;

	i = 1;
	while (arr[i])
	{
		if (arr[i])
			ft_putstr_fd(arr[i], 1);
		if (arr[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putendl_fd("", 1);
}

int     manage_shell(t_cmds  *cmds, t_params *params)
{
	int value;

	value = 0;

	if (cmds->argv[0])
	{
		if (!ft_strcmp(cmds->argv[0], "exit") && ++value)
			ft_exit(cmds, params);
		else if (!ft_strcmp(cmds->argv[0], "cd") && ++value)
			change_dir(cmds->argv, params);
		else if (!ft_strcmp(cmds->argv[0], "setenv") && ++value)
			!cmds->argv[1] ? ft_env(params) : ft_setenv(cmds->argv, params);
		else if (!ft_strcmp(cmds->argv[0], "unsetenv") && cmds->argv[1] && ++value)
			ft_unsetenv(cmds->argv, params);
		else if (!ft_strcmp(cmds->argv[0], "env") && ++value)
			ft_env(params);
		else if (!ft_strcmp(cmds->argv[0], "echo") && ++value)
			ft_echo(cmds->argv);
	}
	return(value);
}

char    *remove_quotes(char *string)
{
	int backslash;
	int i;
	int j;
	char *tmp;

	backslash = 0;
	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	while (string[i])
	{
		if (string[i] == '"' && string[i - 1] != '\\')
		{
			i++;
			while(string[i] && (string[i] != '"' || string[i - 1] == '\\'))
			{
				if (string[i] == '\\' && (string[i + 1] == '\'' || string[i + 1] == '"'))
					i++;

				if (string[i] == '\\')
				{
					if (backslash == 1)
					{ 
						i++;
						backslash = 0;
					}
					else
						backslash = 1;
				}
				tmp[j] = string[i];
				j++;
				i++;
			}
			i++;
		}
		if (string[i] == '\'' && string[i - 1] != '\\')
		{
			i++;
			while(string[i] && (string[i] != '\'' || string[i - 1] == '\\'))
			{
				if (string[i] == '\\' && (string[i + 1] == '\'' || string[i + 1] == '"'))
					i++;

				if (string[i] == '\\')
				{
					if (backslash == 1)
					{ 
						i++;
						backslash = 0;
					}
					else
						backslash = 1;
				}
				tmp[j] = string[i];
				j++;
				i++;
			}
			i++;
		}
		if (string[i] == '\\')
		{
			if (backslash == 0)
			{ 
				i++;
				backslash = 1;
			}
			else
			{
				backslash = 0;
				i++;
			}
		}
		if ((string[i] != '"' && string[i] != '\'') || (string[i - 1] == '\\'))
		{
			tmp[j] = string[i];
			j++;
			i++;
		}
	}
	tmp[j] = '\0';
	free(string);
	//ft_putendl("\nremove_quotes end");
	return (tmp);
}

char		*get_path(t_environnement *args, char *rd)
{
	char **paths;
	int  i = 0;
	char *path;

	if (args->key && !ft_strcmp(args->key, "PATH"))
	{
		paths = ft_strsplit(args->value, ':');
		while (paths[i])
		{
			path = ft_strjoin(paths[i], rd);
			if (!access(path, F_OK))
			{
				//free(rd);
				rd = NULL;
				//free2d(paths);
				return (path);
			}
			//free(path);
			path = NULL;
			i++;
		}
		//free2d(paths);
		//paths = NULL;
		path = NULL;
	}
	return (NULL);
}

char    *get_cmd(char *argv, t_params *params)
{
	t_list          *environnements;
	char            *path;
	char            *ret;
	t_environnement *environnement;

	path = NULL;
	if (argv[0] != '\0')
		path = ft_strjoin("/", argv);
	environnements = params->environnement;
	while (environnements)
	{
		environnement = environnements->content;
		if ((ret = get_path(environnement, path)))
		{
			return (ret);
		}
		if (!access(argv, F_OK) && ft_strchr(argv, '/'))
		{
			free(path);
			path = NULL;
			return (ft_strdup(argv));
		}
		//ft_putendl(environnement->key);
		environnements = environnements->next;
	}
	return (NULL);
}

char    **get_tab_environnement(t_params *params)
{
	t_environnement *env;
	t_list *environnements;
	char **tab;
	char *tmp;
	int  i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (params->envs + 1));
	environnements = params->environnement;
	while (environnements)
	{
		env = environnements->content;
		tmp = ft_strjoin(env->key, "=");
		tab[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		environnements = environnements->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void		execve_child(char **read, char **environment, char *path)
{
	execve(path, read, environment);
	ft_putendl_fd("exec format error", 2);
	exit(0);
}

t_cmds    *remove_quotes_2d(t_cmds *cmds)
{
	int     i;

	i = 0;
	while (cmds->argv[i])
	{
		cmds->argv[i] = remove_quotes(cmds->argv[i]);
		i++;
	}
	return (cmds);
}

int 	manage_sh1(t_params *params)
{
	t_list *lst;
	t_cmds  *cmds;
	int     prev;
	int     next;
	int     pipefd[2];
	t_list *redirections;
	t_redirection *redirection;




	//sleep(1);
	// ft_putendl("\n");
	// put_tst(params->lst);
	// ft_putendl("\n");
	lst = params->lst;
	//int     std[3] = {dup(0), dup(1), dup(2)};
	int std[3];
	std[0] = dup(0);
	std[1] = dup(1);
	std[2] = dup(2);
	prev = 0;
	next = 0;
	while (lst)
	{
		char    **args;
		int     fd;
		redirections = NULL;
		redirection = NULL;
		int err = 0;

		cmds = remove_quotes_2d(lst->content);
		args = cmds->argv;
		redirections = cmds->redirections;
		if (prev != 0)
		{
			dup2(pipefd[0], 0);
			close(pipefd[0]);
		}
		if ((lst)->next || cmds->heredoc)
		{
			pipe(pipefd);
			dup2(pipefd[1], 1); ////
			close(pipefd[1]);
		}
		else
		{
			dup2(std[1], 1);
			dup2(std[2], 2);
		}
		while (redirections && !cmds->heredoc)
		{
			redirection = redirections->content;
			if (redirection->file)
			{
				//( "%d%s,%c"1, fg, df, gd, fg)
				if ((fd = open(redirection->file, redirection->type , 0644)) > 0) 
				{
					dup2(fd, redirection->source_fd);
					if (redirection->source_fd1)
						dup2(fd, redirection->source_fd1);
					close(fd);
				}
				else if (redirection->type == (O_RDONLY) && (err = 1))
				{
					ft_putstr_fd("21sh: ", 2);
					ft_putstr_fd(redirection->file, 2);
					ft_putendl_fd(": No such file or directory", 2);
					//err = 1;
				}
				else if ((redirection->type == one || redirection->type == two) && (err = 1)) // tst ls > /Applications/fdfgls
				{
					ft_putstr_fd("sh: ", 2);
					ft_putstr_fd(redirection->file, 2);
					ft_putendl_fd(": Permission denied", 2);
					//err = 1;
				}
			}
			else if (!redirection->close)
			{
				if (dup2(redirection->destination_fd, redirection->source_fd) == -1 && (err = 1))
				{
					ft_putnbr(redirection->destination_fd);
					ft_putendl(" : Bad file descriptor");
				}
			}
			else if (redirection->close)
			{
				close(redirection->source_fd);
			}
			redirections = redirections->next;
		}
		if (cmds->heredoc)
		{
			ft_putstr(cmds->heredoc);
			free(cmds->heredoc);
			cmds->heredoc = NULL;
			prev++;
			continue ;
		}
		if (err)
		{
			err = 0;
			(lst) = (lst)->next;
			continue ;
		}
		if(!manage_shell(cmds, params))
		{
			char *path;
			if (cmds->argv[0] && (path = get_cmd(cmds->argv[0], params)))
			{
				struct stat st;
				stat(path, &st);
				if (S_ISDIR(st.st_mode))
				{
					ft_putstr_fd(path, 2);
					ft_putendl_fd(" : is a directory", 2);
					(lst) = (lst)->next;
					prev++;
					continue;
				}
				params->environnement_tab = get_tab_environnement(params);
				int pid;

				if (!(pid = fork()))
				{
					close(pipefd[0]);
					execve_child(cmds->argv, params->environnement_tab, path);
				}
			}
			else if (cmds->argv[0])
			{
				ft_putstr_fd(cmds->argv[0], 2);
				ft_putendl_fd(": command not found", 2);
			}
		}
		(lst) = (lst)->next;
		prev++;
	}
	dup2(std[1], 1);
	close(std[1]);
	dup2(std[0], 0);
	close(std[0]);
	dup2(std[2], 2);
	close(std[2]);

	g_child = 1;
	while (wait(0) > 0)
		;
	g_child = 0;
	return (0);
}