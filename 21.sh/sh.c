#include "sh.h"

# define BUF 1

char    *ft_read(char *reads)
{
    char    *buf;
    char    *tmp;

    //buf = (char *)malloc(sizeof(char) * (BUF + 1));
    if(!(buf = ft_memalloc(sizeof(char) * (BUF + 1))))
        return (0);
    reads = ft_strdup("");
    while (read(0, buf, BUF))
    {
        buf[1] = '\0';
        if (ft_strchr(buf, '\n'))
            break;
        tmp = reads;
        reads = ft_strjoin(reads, buf);
                                                    //    free(buf);            //;;; file
                                                                free(tmp);  //;;; file
    }
    free(buf);            //;;; file
                                                    //    free(buf);       ;;; file                           /// i write free in here;   
    return(reads);
}



char    *del_startend_space(char *delete)
{
    int i;
    char *str;

    int len;
    i = 0;
    int j = 0;
    //str = (char *)malloc(sizeof(char) * (len = ft_strlen(delete)));
    if (!(str = ft_memalloc((len = ft_strlen(delete)))))
        return (NULL);
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
    //ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    if  (!(ret = ft_memalloc(ft_strlen(str) + 1)))
        return (0);
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
    char    *value;

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
        if (env->value)
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
    char *tmp;

    dq = 0;
    concatenation = ft_strdup("");
    //dollar = (char *)malloc(sizeof(char) * large_env(params));
    if (!(dollar = ft_memalloc(sizeof(char) * large_env(params))))
        return (0);
    //str = (char *)malloc(sizeof(char) * ft_strlen(string));
    if (!(str = ft_memalloc(sizeof(char) * ft_strlen(string) + 1)))
        return (0);
    i = 0;
    s = 0;
    env = params->environnement;

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
                                                                tmp = concatenation;
            concatenation = ft_strjoin(tmp, str);//
                                                                free(tmp);
                                                                free(str);
            str = ft_strdup("");
            value = dollar_value(params, dollar);
                                                                tmp = concatenation;
            concatenation = ft_strjoin(tmp, value ? value : "");
                                                                free(tmp);
                                                                free(value);        //new5
            continue ;
        }
        if (string[i] == '"')
            dq = !dq;
        str[s] = string[i];
        i++;
        s++;
    }
    str[s] = 0;
    tmp = concatenation;
    concatenation = ft_strjoin(tmp, str);
                                                            free(tmp);
    free(str);
    free(dollar);
                                                            free(string);
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
    //source = (char *)malloc(sizeof(char) * ft_strlen(src));
    if (!(source = ft_memalloc(sizeof(char) * ft_strlen(src))))
        return (0);

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
        char *tmp1;
    
        if (redirection->file == NULL)
        {
            ft_putendl_fd("21sh: parse error near `\\n'", 2);
            return (0);
        }
        //buf = (char *)malloc(sizeof(char) * 351);
        if (!(buf = ft_memalloc(sizeof(char) * 2048)))
            return(0);
        reads = strdup("");
        ft_putstr_fd("heredoc> ", 1);
        while ((len = read(0, buf, 350)))
        {
            buf[len - 1] = 0;
            if (!ft_strcmp(buf, redirection->file))
                break ;
            tmp = reads;
            tmp1 = ft_strjoin(buf, "\n");
            reads = ft_strjoin(tmp, tmp1);
            free(tmp1);
            free(tmp);
            ft_putstr_fd("heredoc> ", 1);
            ft_bzero(buf, 2047);
        }
        free(tcmds->heredoc);
        tcmds->heredoc = reads; 
        free(redirection->file); //// file ;;;;;;
        redirection->file = NULL;
        free(buf);      //new
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
    int len = 0;
    while (arg[len])
        len++;
    int i = 0;
    while (i < len)
    {
        if ((arg[i]) == '\'')
        {
            i++;
            while (arg[i] != '\'')
                i++;
            i++;
            continue ;
        }
        if ((arg[i]) == '"')
        {
            i++;
            while (arg[i] != '"')
                i++;
            i++;
            continue ;
        }
        if((arg[i]) == '>')
        {
            while (arg[i] == '>')
            {
                i++;
                ret++;
            }
            if (ret > 2)
                return(ret);
            ret = 0;
        }
        if (arg[i] == '<')
        {
            while (arg[i] == '<')
            {
                i++;
                ret++;
            }
            if (ret > 2)
                return(ret);
            ret = 0; 
        }
        i++;
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

int     ft_count_words(char **args)
{
    int len;

    len = 0;
    while (args[len])
        len++;
    return (len + 1);
}

int     check_missing(char **pipes, t_params *params)
{
    char **args;
    int i;
    int j;

    i = 0;
    while (pipes[i])
    {

        pipes[i] = tabs_to_spaces(pipes[i]);
        args = quotes_splite(pipes[i], ' ');
                                                                         //    free(pipes[i]); /// ;;;; file  //new
        j = 0;
        while(args[j])
        {  
           //           static int i; if (i == 1){exit(1);}; i++;
            if (((ft_strchr(args[j], '>')  || ft_strchr(args[j], '<')) && args[j + 1] && (ft_strchr(args[j + 1], '<') || ft_strchr(args[j + 1], '>'))) || superior(args[j], j, args))
            {
                free2d(args);
                free2d(pipes);
                
                //free(params->semicolone);
                

                //  free(args[j]);
                
                //  free(args);
                //                 //free(pipes[i]);
                // free(pipes);
                //ft_free_cmds(*lst);
                ft_putendl_fd("Missing name for redirect.", 2);
                return (0);
            }
            j++;
            
        }
        free2d(args);
        i++;
    }
    return (1);
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
    char            *tmp;


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
    if (!(check_missing(pipes, params)))
        return (0);
    while (pipes[i])
    {

        // pipes[i] = tabs_to_spaces(pipes[i]);             //free >>>
        args = quotes_splite(pipes[i], ' ');
                                                                             free(pipes[i]); /// ;;;; file  //new
        j = 0;
        k = -4;

        if (!(argv = (char **)malloc(sizeof(char *) * ft_count_words(args))))                        /// number exact ... here;  //new4
            return (0);
        if (!(tcmds = (t_cmds *)malloc(sizeof(t_cmds))))
            return (0);
        tcmds->heredoc = NULL;
        red = 0;
                                //static int i; if (i == 1){exit(1);}; i++;
        while(args[j])
        {  

            if (args[j][0] == '~' && (!args[j][1] || args[j][1] == '/'))
            {
                tmp = args[j];   
                args[j] = get_home(params, args[j]);
                free(tmp);
            }

           
           // static int i; if (i == 1){exit(1);}; i++;
            if (((ft_strchr(args[j], '>')  || ft_strchr(args[j], '<')) && args[j + 1] && (ft_strchr(args[j + 1], '<') || ft_strchr(args[j + 1], '>'))) || superior(args[j], j, args))
            {
                free(args[j]);
                
                free(args);
                                //free(pipes[i]);
                free(pipes);
                //ft_free_cmds(*lst);
                ft_putendl_fd("Missing name for redirect.", 2);
                return (0);
            }

             
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
                {
                    free(args[j]);
                    j++;
                }
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

                                        //exit(1);
        free(args);
        i++;

    }

                                                                                        free(pipes); //     ;;;; file
                                                                                        //free(args);
                                            

    //params->args = args;
    i = 0;
    return (1);
}

int        ft_separation(t_list **lst, char *read, t_params *params)  
{
    char **pipes;

    pipes = quotes_splite(read, '|');
    free(read);
    if (ft_getargs(pipes, lst, params) == 0)
        return (0);
    // ft_free_lst(*lst);
    // exit(1);
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
            free(read);
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
                                                                                            free(read);////  ;;; free //new1
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
        {
            return (0);
        }
    }
    return (1);
}

int         skip_semi(char *semi)
{
    int i;
    int len;

    i = 0;
    while (semi[i])
    {  
        while (semi[i] && (semi[i] == ' ' || semi[i] == '\t'))
            i++;
        if (semi[i] == '\0' || semi[i] == ';')
            return (0);
        else
            break;
        //i++;
    }
    return(1);
}

int       errors_semicolone(char **semicolone, char *read)
{
    int i;

    i = 0;
    while(semicolone[i])
    {
        ft_putendl(semicolone[i]);
        if (skip_semi(semicolone[i]) < 1)
        {
                ft_putendl_fd("21sh : syntax error near unexpected token `;'", 2);
                                                                                 free2d(semicolone);                 // new;
                                                                                 free(read);
                                                                                 semicolone = NULL;
                return (0);
        }
        i++;
    }
    return(1);
}

int        splite_semi(char *read, t_list **lst, t_params *params)
{
    int i;
    i = 0;
    char **semicolone = NULL;

    //params->semicolones = NULL;
    semicolone = quotes_splite(read, ';');


    if (!errors_semicolone(semicolone, read))
       return(0);
    //params->sems1 = i;
    while (semicolone[i])
    {
        //params->sems2 = i;
        if (handler_reads(semicolone[i], lst, params) == 0)
        {
            free(read);
            free(semicolone);
            return (0);
        }
       // exit (1);                                   // i am here for free tsts
        params->lst = *lst;
        manage_sh(params);

                                                            //free_params(params);                           ;;;;;;;
                                                        // free(semicolone[i]);
        //semicolone[i] = NULL;
        i++;
    }
            //ft_putstr("\n - semi1 is : ");ft_putnbr(params->sems1);   ft_putstr(" *** - semi2 is : ");ft_putnbr(params->sems2);ft_putendl_fd("\n", 1);
                    //free2d(semicolone);                                                  
                                                                            free(semicolone); //for tst segfault ;;;;;;
                                    //semicolone = NULL;
    return (1);          
}

int     check_semicolone(char *semicolones)
{
    int i;
    int s;
    char q;

    i = 0;
    while (semicolones[i])
    {
        while (semicolones[i] == ' ' || semicolones[i] == '\t')
            i++;
        if (semicolones[i] == '\'' || semicolones[i] == '"')
        {
            q = semicolones[i];
            i++;
            while (semicolones[i] != q)
                i++;
            i++;
            continue ;
        }
        if (semicolones[i] && semicolones[i + 1] && semicolones[i] == ';' && semicolones[i + 1] == ';')
        {
                ft_putendl_fd("21:  : syntax error near unexpected token `;;'", 2);
                                                                                                free(semicolones);   //;;; file //new
                                                                                                semicolones = NULL;             //new
                return (0);
        }
        i++;
    }
    return(1);
}

void    sh(t_params *params)
{
    char *read;
    t_list *lst;
   
    lst = NULL;
    read = NULL;
    while ("21sh")
    {
        ft_putstr_fd("$> ", 1);
        read = ft_read(read);
        if (!check_semicolone(read))
            continue ;
        if (splite_semi(read, &lst, params) == 0)
            continue ;


    //    ft_putstr("\n - semi1 is : ");ft_putnbr(params->sems1);   ft_putstr(" *** - semi2 is : ");ft_putnbr(params->sems2);ft_putendl_fd("\n", 1);
                                                                        // if (params->sems1 == params->sems2 + 1)
                                                                              free(read);           //new
                                                                              read = NULL;          //new
        //free_params(params);
        
        //ft_free_env(params->environnement);
        //free(read); 
                                             ft_free_lst(params->lst);        //new                               //i make free in here;
                                             //free(lst);                       //new 
        lst = NULL;
    }
}

int		main(int ac, char **av, char **env)
{
    t_params *params;

    fprinf_fd = fopen("/dev/ttys001", "a+");
    if (!(params = (t_params*)malloc(sizeof(t_params))))
        return(0);
    //            params = ft_memalloc(sizeof(params));
    params->envs = 0;
    get_environnement(params, env);

    /// to here is free ;
    sh(params);
    (void)ac;
    (void)av;
	return 0;
}
