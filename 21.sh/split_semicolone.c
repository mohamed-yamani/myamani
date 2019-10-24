#include "sh.h"

char		**quotes_splite(char const *s, char c)
{
	char	**str;
	int		start;
	int		index;
	int		words;

	start = 0;
	index = 0;
	words = 0;
	str = NULL;
	if (!s)
		return (NULL);
	int count = ft_countwords(s, c);
	if (!(str = (char **)ft_memalloc(sizeof(char *) * (count + 1))))
		return (NULL);
	int len = ft_strlen(s);
	while (index < len)
	{
        while (s[index] == c)
            index++;
		start = index;
		
		while (index < len && (s[index] != c) && s[index])
		{
			if (s[index] == '\"')
			{
				index++;
				while (s[index] != '\"' && s[index])
					index++;
			}
			if (s[index] == '\'')
			{
				index++;
				while (index < len && s[index] != '\'' && s[index])
				{	
					if (s[index] == '\0')
					{
						ft_putendl_fd("Unmatched \'.", 2);
						exit (1);
					}
					index++;
				}
			}
			index++;
		}
		if (index > start)
			str[words++] = ft_strsub(s, start, (index - start));
	}
	str[count] = NULL;
	return (str);
}


//cmd "tst;;;;;;;tst1"