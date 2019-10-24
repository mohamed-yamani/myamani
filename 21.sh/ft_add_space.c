#include "sh.h"

int             ft_isalnum1(char *read, int i)
{
    int r = 1;
    while (read[i] == ' ')
    {
        i++;
        r++;
    }
    while (read[i] >= '0' && read[i] <= '9')
        i++;
    if (read[i] == ' ' || read[i] == '\0')
    {
        i++;
        return (r);
    }
    else
        return (0);
}


char    *save_quotes(char *reads, char *tmp, int i, int j)
{
    char *quotes;
    int q;
    
    quotes = NULL;
    if (reads[i] == '"' || reads[i] == '\'')
    {
        q = reads[i];
        tmp[j] = reads[i];
        i++;
        j++;
        while(reads[i] != q)
        {
            tmp[j] = reads[i];
            i++;
            j++;
        }
        tmp[j] = reads[i];
        i++;
        j++;
    }
    // ft_putstr("\n in function : ");
    // ft_putnbr(i);ft_putnbr(j);
    return (quotes);
}

int     len_for_spaces(char *reads)
{
    int i;
    int q;
    int k = 0;
    int len = 1;

    i = 0;
    while (reads[i])
    {
        if (reads[i] == '"' || reads[i] == '\'')
        {
            q = reads[i];
            i++;
            while(reads[i] != q)
                i++;
            i++;
            continue ;
        }
        if (reads[i] == '&' && reads[i + 1] && reads[i + 1] == ' ')
        {
            i++;
            while (reads[i] == ' ')
                i++;
            if (reads[i] && reads[i] != '>' && reads[i] != '<' && reads[i] != '-')
                i--;
            continue ;
        }
        if ((reads[i] == '>' || reads[i] == '<') && reads[i + 1] && reads[i + 1] == ' ')
        {
            i++;
            while (reads[i] == ' ')
                i++;
            if (reads[i] != '&')
                i--;
            continue ;
        }

        if (ft_isdigit(reads[i]) && reads[i - 1] == ' ')
        {
            k = i;
            int x = 0;
            while(reads[i])
            {
                if (reads[i] == '>')
                {
                    i++;
                    x = 0;
                    break;
                }
                if (!ft_isdigit(reads[i]) || !reads[i + 1] /*|| reads[i] != '>'*/)
                {
                    i = k;
                    x = 0;
                    break;
                }
                x++;
                i++;
            }
        }
        if (ft_isdigit(reads[i]) && reads[i - 1] == ' ')
        {
            k = i;
            int x = 0;
            while(reads[i])
            {
                if (reads[i] == '<')
                {
                    i++;
                    break;
                }
                if (!ft_isdigit(reads[i]) || !reads[i + 1] /*|| reads[i] != '>'*/)
                {
                    i = k;
                    x = 0;
                    break;
                }
                x++;
                i++;
            }
        }
        if (i > 0 && ((reads[i - 1] == '|' && reads[i] != ' ') || (reads[i - 1] == '>' && reads[i] != ' ' && reads[i] != '>' && reads[i] != '&') || (reads[i - 1] == '<' && reads[i] != ' ' && reads[i] != '<' && reads[i] != '&') || (reads[i - 1] == '&' && (reads[i] != '>' && reads[i] != '<') && reads[i] != '-')) /*&& !q && !dq && reads[i] != '"' && reads[i] != '\''*/)
            len++;
        if (reads[i + 1] && ((reads[i + 1] == '|' && reads[i] != ' ') || (reads[i + 1] == '>' && reads[i] != ' ' && reads[i] != '>' && reads[i] != '&') || (reads[i + 1] == '<' && reads[i] != ' ' && reads[i] != '<' && reads[i] != '&') || (reads[i + 1] == '&' && (reads[i] != '>' && reads[i] != '<') && reads[i] != '-')) /*&& !q && !dq && !ft_isdigit(reads[i])*/)
            len++;
        i++;
        while (reads[i] && reads[i] == ' ' && reads[i + 1] == ' ')
            i++;
    }
    return (len);
}

char    *ft_add_space(char *reads)
{
    int i;
    int j;
    int k;
    char *tmp;
    char *tmp1;
    char *tmp2;
    char q;

    i = 0;
    j = 0;
    k = 0;
    int len = ft_strlen(reads);
    //ft_putendl(" a file is here ft_add_space ");
    
    tmp = (char *)ft_memalloc(sizeof(char) * len + len_for_spaces(reads));
//    tmp1 = (char *)malloc(sizeof(char) * 255);

    while (reads[i])
    {
        if (reads[i] == '"' || reads[i] == '\'')
        {
            q = reads[i];
            tmp[j] = reads[i];
            i++;
            j++;
            while(reads[i] != q)
            {
                tmp[j] = reads[i];
                i++;
                j++;
            }
            tmp[j] = reads[i];
            i++;
            j++;
            continue ;
        }
        if (reads[i] == '&' && reads[i + 1] && reads[i + 1] == ' ')
        {
            tmp[j] = reads[i];
            j++;
            i++;
            while (reads[i] == ' ')
                i++;
            if (reads[i] && reads[i] != '>' && reads[i] != '<' && reads[i] != '-')
                i--;
            continue ;
        }
        if ((reads[i] == '>' || reads[i] == '<') && reads[i + 1] && reads[i + 1] == ' ')
        {
            tmp[j] = reads[i];
            i++;
            j++;
             while (reads[i] == ' ')
                i++;
            if (reads[i] != '&')
                i--;
            continue ;
        }

        if (ft_isdigit(reads[i]) && reads[i - 1] == ' ')
        {
            k = i;
            int x = 0;
            tmp1 = (char *)malloc(sizeof(char) * 255);
            while(reads[i])
            {
                tmp1[x] = reads[i];

                if (reads[i] == '>')
                {
                    i++;
                    j = j+x+1;
                    tmp1[x + 1] = '\0';
                    x = 0;//
                    tmp2 = tmp;
                    tmp = ft_strjoin(tmp, tmp1);
                    // free(tmp2);
                    // free(tmp1);
                    break;
                }
                if (!ft_isdigit(reads[i]) || !reads[i + 1] /*|| reads[i] != '>'*/)
                {
                    i = k;
                    x = 0;
                    free(tmp1);
                    break;
                }
                x++;
                i++;
            }
        }
        if (ft_isdigit(reads[i]) && reads[i - 1] == ' ')
        {
            k = i;
            int x = 0;
            tmp1 = (char *)malloc(sizeof(char) * 255);
            while(reads[i])
            {
                tmp1[x] = reads[i];

                if (reads[i] == '<')
                {
                    i++;
                    j = j + x + 1;
                    tmp1[x + 1] = '\0';
                    x = 0;
                    tmp = ft_strjoin(tmp, tmp1);
                    break;
                }
                if (!ft_isdigit(reads[i]) || !reads[i + 1] /*|| reads[i] != '>'*/)
                {
                    i = k;
                    x = 0;
                    break;
                }
                x++;
                i++;
            }
        }
        if (i > 0 && ((reads[i - 1] == '|' && reads[i] != ' ') || (reads[i - 1] == '>' && reads[i] != ' ' && reads[i] != '>' && reads[i] != '&') || (reads[i - 1] == '<' && reads[i] != ' ' && reads[i] != '<' && reads[i] != '&') || (reads[i - 1] == '&' && (reads[i] != '>' && reads[i] != '<') && reads[i] != '-')) /*&& !q && !dq && reads[i] != '"' && reads[i] != '\''*/)
            tmp[j++] = ' ';
        tmp[j] = reads[i];
        if (reads[i + 1] && ((reads[i + 1] == '|' && reads[i] != ' ') || (reads[i + 1] == '>' && reads[i] != ' ' && reads[i] != '>' && reads[i] != '&') || (reads[i + 1] == '<' && reads[i] != ' ' && reads[i] != '<' && reads[i] != '&') || (reads[i + 1] == '&' && (reads[i] != '>' && reads[i] != '<') && reads[i] != '-')) /*&& !q && !dq && !ft_isdigit(reads[i])*/)
            tmp[++j] = ' ';
        if (reads[i] == '&' && !ft_isalnum1(reads, i + 1) && reads[i + 1] != '-' && (reads[i - 1] == '>' || reads[i - 1] == '<' ))                //tst here !
        {
            ft_putendl_fd("Missing name for redirect.", 2);
            free(reads);
            return (NULL) ;
        }

        i++;
        j++;

        while (reads[i] && reads[i] == ' ' && reads[i + 1] == ' ')
            i++;
    }
    tmp[j] = '\0';
    printf("tmp = |%s| j == %d, len = %d, len_of_spaces = %d\n", tmp, j, len, len_for_spaces(reads));
    // printf("ft_add space ** reads adress-> %p > value -> '%s'\n", reads, reads);
    // printf("ft_add space ** tmp adress-> %p > value -> '%s'\n", tmp, tmp);
    free(reads);
    // if (tmp[ft_strlen(tmp - 1)] == '>')
    // {
    //     ft_putendl("Missing name for redirect. ****");
    //     free(tmp);
    //     return (NULL);
    // }
    //sleep(2);
    return (tmp);
}