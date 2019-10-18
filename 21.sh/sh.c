#include "sh.h"

# define BUF 1

char    *ft_read(char *reads)
{
    char    *buf;
    char    *tmp;

    buf = (char *)malloc(sizeof(char) * (BUF + 1));
    reads = ft_strdup("");
    while (read(0, buf, BUF))
    {
        buf[1] = '\0';
        if (ft_strchr(buf, '\n'))
            break;
        tmp = reads;
        reads = ft_strjoin(reads, buf);
        free(tmp);
    }
    return(reads);
}



char    *del_startend_space(char *delete)
{
    int i;
    char *str;

    int len;
    i = 0;
    int j = 0;
    str = (char *)malloc(sizeof(char) * (len = ft_strlen(delete)));
    while (delete[i])
    {
        if (i == 0 && delete[i] == ' ')
            i++;
        str[j] = delete[i];
        if (i == len && delete[i] == ' ')
            break ;
        i++;
        j++;
    }
    str[j] = '\0';
    return (str);
}

int     ft_calcul_cmd(char *cmd)
{
    int i;
    char **tst;

    i = 0;
    tst = ft_strsplit(cmd, ' ');
    while (tst[i])
        i++;
    return (i);
}

int     is_number(char *str)
{
    int i;
    i = 0;

    while (str[i])
    {
        if (ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int     get_type(char *arg)
{
    int i;
    int type;

    i = 0;
    type = -1;
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]))
        {
            if (arg[i] == '>' && type == -1)
                type = one;
            else if (arg[i] == '>' && type == one)
                type = two;
            else if (arg[i] == '>' && type == two)
            {
                ft_putstr_fd("21sh: parse error near `>", 2);
                if (arg[i + 1] == '>')
                    ft_putchar_fd(arg[i++], 2);
                ft_putendl_fd("\'", 2);
                return(-1);
            }
            if (arg[i] == '<')
            {
                if (type == -1)
                    type = (O_RDONLY);    ///////////// here 3
                else if (type == (O_RDONLY))      ///////////// here 3
                    type = 4;
                else
                {
                  ft_putendl_fd("21sh: parse error near `<\'", 2);
                  return (0);
                }
            }
        }
        i++;
    }
    //ft_putnbr(type);
    return (type);
}

char    *del_quotes(char *str)
{
    int i;
    int j;
    char *ret;

    i = 0;
    j = 0;
    ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            i++;
        ret[i] = str[i];
        i++;
        j++;
    }
    ret[i] = '\0';
    free(str);
    return (ret);
}

char    *dollar_value(t_params *params, char *dollar)
{
    t_list *env;
    t_environnement *environnement;
    t_list *head;
    char *value;

    env = params->environnement;
    head = env;
    value = NULL;
    while (head)
    {
        environnement = head->content;
        if (!ft_strcmp(environnement->key, dollar))
        {
            if (environnement->value)
                value = ft_strdup(environnement->value);
            else
                value = NULL;
        }
        head = head->next;
    }
    return(value);
}

int     large_env(t_params *params)
{
    t_list *envs;
    t_environnement *env;
    int len;
    int len1;

    len = 0;
    len1 = 0;
    envs = params->environnement;
    while (envs)
    {
        env = envs->content;
        len1 = ft_strlen(env->value);
        if (len1 > len)
            len = len1;
        envs =envs->next;
    }
    // printf("len is :%d\n", len);
    // sleep(2);
    return (len);
}

char    *checking_dollar(char *string, t_params *params)
{
    t_list *env;
    char *dollar;
    int i;
    int d;
    char    *str;
    char    *concatenation;
    int     s;
    char       *value;
    int dq;

    dq = 0;
    concatenation = ft_strdup("");
    dollar = (char *)malloc(sizeof(char) * large_env(params));
    str = (char *)malloc(sizeof(char) * ft_strlen(string));
    i = 0;
    s = 0;
    env = params->environnement;




            printf("my error in here 1 \n");
    while (string[i])
    {
        if (string[i] == '\'' && !dq)
        {
            str[s++] = string[i++];
            while (string[i] && string[i] != '\'')
               str[s++] = string[i++];   
            str[s] = string[i];
            if (string[i + 1] && (s++) && (i++))
                ;
            else
               str[s] = 0;
        }

        if (string[i] == '$' && string[i + 1] && string[i + 1] != '"')
        {
            d = 0;
            s = 0;

            i++;
            while (string[i] && string[i] != ':' && string[i] != '/' && string[i] != '$' && string[i] != '"' && string[i] != '\'' && string[i] != '\\') 
            {
                dollar[d] = string[i];
                i++;
                d++;
            }
            dollar[d] = '\0';
            concatenation = ft_strjoin(concatenation, str);//
            str = ft_strdup("");
            value = dollar_value(params, dollar);
            concatenation = ft_strjoin(concatenation, value ? value : "");
            continue ;
        }
        if (string[i] == '"')
            dq = !dq;
        str[s] = string[i];
        i++;
        s++;
    }
    str[s] = 0;
    concatenation = ft_strjoin(concatenation, str);
    free(dollar);

    return (concatenation);
}

char    *tabs_to_spaces(char *str)
{
    int i;
    i = 0;

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            i++;
            while (str[i] && (str[i] != '"' || str[i] != '\''))
                i++;
        }
        if (str[i] == '\t')
            str[i] = ' ';
        i++;
    }
    return (str);
}

int    get_source_fd(char *src, t_redirection *redirection)
{
    char *source;
    int i;
    int sr;

    i = 0;
    source = (char *)malloc(sizeof(char) * ft_strlen(src));

    if (!ft_strcmp(src, "&>"))
        {
            redirection->source_fd1 = 2;
            return (1);
        }
    if (strchr(src, '>'))
        while (src[i] != '>')
        {
            source[i] = src[i];
            i++;
        }
    else if (strchr(src, '<'))                          ////                for '<'
        while (src[i] != '<')
        {
            source[i] = src[i];
            i++;
        }
    else
        return (1);
    source[i] = '\0';
    sr = ft_atoi(source);
    free(source);
    if (src[0] == '>')
        return(1);
    return (sr);
}

int     get_heredoc(t_redirection *redirection, t_cmds *tcmds)
{
    if (redirection->type == 4)
    {
        char    *buf;
        char    *tmp;
        char    *reads;
        int     len;
    
        if (redirection->file == NULL)
        {
            ft_putendl_fd("21sh: parse error near `\\n'", 2);
            return (0);
        }
        buf = (char *)malloc(sizeof(char) * 351);
        reads = strdup("");
        ft_putstr_fd("heredoc> ", 1);
        while ((len = read(0, buf, 350)))
        {
            buf[len - 1] = 0;
            if (!ft_strcmp(buf, redirection->file))
                break ;
            tmp = reads;
            reads = ft_strjoin(reads, ft_strjoin(buf, "\n"));
            free(tmp);
            ft_putstr_fd("heredoc> ", 1);
            ft_bzero(buf, 350);
        }
        tcmds->heredoc = reads; 
        free(redirection->file);
        redirection->file = NULL;
    }
    return (1);
}

int     check_superior(char *arg, int j, char **args)
{
    int size;

    size = ft_strlen(arg);
    if ((arg[size - 1] == '>' || arg[size - 1] == '<') && !args[j + 1])
        return (1);
    if (arg[size - 1] && arg[size - 2] && arg[size - 1] == '&' && (arg[size - 2] == '>' || arg[size - 2] == '<') && !args[j + 1])
        return (1);
    if (arg[size - 1] && arg[size - 2] && arg[size - 2] == '&' && (arg[size - 1] == '>' || arg[size - 1] == '<') && !args[j + 1])
        return (1);
    return (0);
}

int     superior(char *arg, int j, char **args)
{
    int ret = 0;

    if (ft_strstr(arg, ">&") && args[j + 1])
        return (0);
    if (check_superior(arg, j, args))
        return (1);
    while (*arg)
    {
        if ((*arg) == '\'')
        {
            arg++;
            while (*arg != '\'')
                arg++;
            arg++;
            continue ;
        }
        if ((*arg) == '"')
        {
            arg++;
            while (*arg != '"')
                arg++;
            arg++;
            continue ;
        }
        if((*arg) == '>')
        {
            while (*arg == '>')
            {
                arg++;
                ret++;
            }
            if (ret > 2)
                return(ret);
            ret = 0;
        }
        if (*arg == '<')
        {
            while (*arg == '<')
            {
                arg++;
                ret++;
            }
            if (ret > 2)
                return(ret);
            ret = 0; 
        }
        arg++;
    }
    return (0);
}

char *get_home(t_params *params, char *string)
{
    t_list *envs;
    t_environnement *env;
    char *str;

    str = NULL;

    envs = params->environnement;
    while (envs)
    {
        env = envs->content;
        if (!ft_strcmp(env->key, "HOME"))
            str = ft_strdup(env->value);
        envs = envs->next;
    }
    if (string[1] && str)
        str = ft_strjoin(str, string + 1);
    return (str);
}

int     ft_sep(char *arg)
{
    int i;
    
    i = 0;
    char q;
    while (arg[i])
    {
        if (arg[i] == '\'' || arg[i] == '"')
        {
            q = arg[i];
            i++;
            while (arg[i] && arg[i] != q)
            {
                i++;
            }
            if (arg[i] == '\0')
                return (0);
            else
                i++;
            continue ;
        }
        if (arg[i] == '>' || arg[i] == '<')
            return (1);
        i++;
    }
    return (0);
}

int    ft_getargs(char **pipes, t_list **lst, t_params *params)
{
    int i;
    t_list *list;
    t_cmds *tcmds;
    char **args;
    t_redirection   *redirection;
    t_list          *redirections;
    t_list          *list_redi;
    int             red;
    int             d;


    i = 0;
    d = 0;
    int j;
    int k;
    red = 0;
    char **argv;
    int a;
    a = 0;
    redirections = NULL;
    args = NULL;

    while (pipes[i])
    {
        pipes[i] = tabs_to_spaces(pipes[i]);
        args = quotes_splite(pipes[i], ' ');

        j = 0;
        k = -4;
        argv = (char **)malloc(sizeof(char *) * 10);
        tcmds = (t_cmds *)malloc(sizeof(t_cmds));
        tcmds->heredoc = NULL;
        red = 0;
        while(args[j])
        {   
            if (args[j][0] == '~' && (!args[j][1] || args[j][1] == '/'))
                args[j] = get_home(params, args[j]);
            if (((ft_strchr(args[j], '>')  || ft_strchr(args[j], '<')) && args[j + 1] && (ft_strchr(args[j + 1], '<') || ft_strchr(args[j + 1], '>'))) || superior(args[j], j, args))
            {
                ft_putendl_fd("Missing name for redirect.", 2);
                return (0);
            }
            // ft_putnbr(ft_sep(args[j]));ft_putendl(args[j]);
            // sleep(2);
            
            if (ft_sep(args[j]))//if ((ft_strchr(args[j], '>') || ft_strchr(args[j], '<')) && ft_sep(args[j]))
            {
                redirection = (t_redirection *)malloc(sizeof(t_redirection));
                ft_initialisation(redirection);
                redirection->source_fd = get_source_fd(args[j], redirection);
                if (args[j] && ft_strchr(args[j], '&') && ft_strchr(args[j], '-'))
                    redirection->close = 1;
                else if (ft_strchr(args[j], '&') && args[j + 1] && !is_number(args[j + 1]))
                    redirection->destination_fd = ft_atoi(args[j + 1]);       
                else if (args[j] && args[j + 1])
                    redirection->file = checking_dollar((args[j + 1]) ? args[j + 1] : NULL, params);
                redirection->type = get_type(args[j]);
                if (get_heredoc(redirection, tcmds) == 0)
                    return (0);
                if (args[j + 1])
                    j++;
                k = j;
                list_redi = ft_listnew(redirection);
                ft_lstadd1(&redirections, list_redi);
                redirection = NULL;
                red++;
            }
            if (j != k)
            {
                if (ft_strchr(args[j], '$'))
                    args[j] = checking_dollar(args[j], params);
                argv[a] = args[j];
                a++;
            }
            // ft_putstr("<<< ");
            // ft_putstr(args[j]);
            // ft_putendl(" >>>");
            // sleep(1);
            j++;
        }   
        argv[a] = NULL;
        tcmds->argv = argv;
        tcmds->i = i;
        tcmds->redirections = redirections;
        redirections = NULL;        
        a = 0;
        list = ft_listnew(tcmds);    
        ft_lstadd1(lst, list);
        i++;
    }
    return (1);
}

int        ft_separation(t_list **lst, char *read, t_params *params)  
{
    char **pipes;

    pipes = quotes_splite(read, '|');
    // char **tmp;
    // tmp = pipes;
    // int i = 0;
    // while (tmp[i])
    // {
    //     ft_putstr(">>>");ft_putendl(tmp[i]);ft_putstr("<<<");
    //     i++;
    // } 
    if (ft_getargs(pipes, lst, params) == 0)
        return (0);
    return (1);
}

int         pipes_num(char *read)
{
    int i;
    int max;
    char q;
    
    i = 0;
    max = 0;
    while (read[i] == ' ' || read[i] == '\t' || read[i] == '|')
    {
        if (read[i] == '|')
        {
            ft_putendl("bash: syntax error near unexpected token `|'");
            return (0);
        }
        i++;
    }
    i = 0;
    while (read[i])
    {
        if (read[i] == '\'' || read[i] == '"')
        {
            q = read[i];
            i++;
            while(read[i] && read[i] != q && read[i - 1] != '\\')
                i++;
            if (read[i])
                i++;
            continue;
        }
        if (read[i] == '|')
        {
            max = 0;
            while (read[i] && read[i] == '|')
            {
                if (read[i + 1])
                    i++;
                max++;
                if (max == 2)
                {
                    free(read);
                    ft_putendl_fd("Invalid null command.", 2);
                    return (0);
                }
            }
        }
        i++;
    }
    return (1);
    
}

int        handler_reads(char *read, t_list **lst , t_params *params)
{
    //ft_putstr("pipes is : "); ft_putendl(read);ft_putstr(" >>>");
    if (!pipes_num(read))
        return (0);
    if ((read = ft_add_space(read)))
    {
        if (ft_separation(lst, read, params) == 0)
            return (0);
    }
    return (1);
}

int        splite_semi(char *read, t_list **lst, t_params *params)
{
    int i;
    i = 0;
    char **semicolone = NULL;

    params->semicolones = NULL;
    semicolone = quotes_splite(read, ';');
    while (semicolone[i])
    {
        if (handler_reads(semicolone[i], lst, params) == 0)
            return (0);
        
        params->lst = *lst;
        manage_sh1(params);
        i++;
    }
    return (1);          
}

void    sh(t_params *params)
{
    char *read;
    t_list *lst;
   
    lst = NULL;
    read = NULL;
    params->semicolones = NULL;
    while ("21sh")
    {
        ft_putstr_fd("$> ", 1);
        read = ft_read(read);
        if (splite_semi(read, &lst, params) == 0)
            continue ;
        free(lst);
        free(read);                                             //i make free in here;
        lst = NULL;
    }
}

int		main(int ac, char **av, char **env)
{
    t_params *params;

    fprinf_fd = fopen("/dev/ttys001", "a+");
    params = (t_params*)malloc(sizeof(t_params));
    params->envs = 0;
    get_environnement(params, env);
    sh(params);
    (void)ac;
    (void)av;
	return 0;
}
