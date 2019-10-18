
#include "sh.h"

void    ft_exit(t_cmds  *cmds, t_params *params)
{
    
    ft_putendl("is exit");
    free(cmds);
    free(params);
    exit(0);
}