#include "sh.h"

void    free2d(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
  //      ft_putendl(arr[i]);
        free(arr[i]);
        i++;
    }
                             free(arr[i]);          //new
                            free(arr);    //;;      //new
    
}