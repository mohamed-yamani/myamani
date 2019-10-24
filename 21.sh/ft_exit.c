
#include "sh.h"

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        tab[i] = NULL;
        i++;
    }
}

void    free_redirections(t_list *lst)
{
    t_redirection *redirection;
    t_list *tmp;

    while(lst)
    {
        redirection = lst->content;
        free(redirection->file);
        free(redirection);
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
}

void    ft_free_cmds(t_list *lst)
{
     t_list *tmp;
    t_cmds *cmd;
    t_list          *redirections;
    t_redirection   *redirection;

    while (lst)
    {
        cmd = lst->content;
        int i = 0;
        free2d(cmd->argv);
        redirections = cmd->redirections;
        if (redirections)
            while (redirections)
            {
                redirection = redirections->content;
                if (redirections && redirection->file)
                   free(redirection->file);
                free(((t_redirection *)redirections->content));
                tmp = redirections;
                redirections = redirections->next;
                free(tmp);
            }
        tmp = lst;
        free(cmd); //  ';;;;'   //new
        lst = lst->next;
        free(tmp);  //   ';;;;' //new
    }
    free(lst);
    // //ft_putstr(" *** ");
    // ft_putstr(cmds->argv[0]);ft_putstr(" *** \n");
    // //sleep(2);
    // free_tab(cmds->argv);
    // //free(cmds->heredoc);
    // //free_redirections(cmds->redirections);
}


void    ft_free_lst(t_list *lst)
{
    t_list *tmp;
    t_cmds *cmd;
    t_list          *redirections;
    t_redirection   *redirection;

    while (lst)
    {
        cmd = lst->content;
        int i = 0;
        free2d(cmd->argv);
        redirections = cmd->redirections;
        if (redirections)
            while (redirections)
            {
                redirection = redirections->content;
                // if (redirections && redirection->file)
                //    free(redirection->file);
                                                            free(((t_redirection *)redirections->content));
                tmp = redirections;
                redirections = redirections->next;
                free(tmp);
            }
        tmp = lst;
                                                                            free(cmd); //  ';;;;'   //new
        lst = lst->next;
                                                                              free(tmp);  //   ';;;;' //new
    }
    free(lst);
}

void    ft_free_env(t_list *envs)
{
    t_environnement *env;
    t_list *tmp;

    while (envs)
    {
        env = envs->content;
        //ft_putendl(env->key);
        free(env->key);
        free(env->value);
        free(env);
        tmp = envs;
        envs = envs->next;
        free(tmp);
    }
    free(envs);
}

void    free_params(t_params *params)
{
    ft_free_lst(params->lst);
    
    //free(params->args);
}

void    free_params1(t_params *params)
{
    //ft_free_lst(params->lst);
    free(((t_cmds *)params->lst)->argv);
    //free(params->args);
}

void    free_env_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        tab[i] = NULL;
    }
    free(tab[i]);
    tab[i] = NULL;
}

void    ft_exit(t_cmds  *cmds, t_params *params)
{
    free_params(params);
     ft_free_env(params->environnement);
     //free_env_tab(params->environnement_tab);
    ft_putendl("is exit");
        //free(params);
                                             //free(cmds);
                                            // free(params);
    exit(0);
}