#include <stdlib.h>
#include <unistd.h>

void	brainfuck(char *str)
{
	int	tab[2048] = {0};
	int	*ptr;
	int	loop_count;

	ptr = tab;
	loop_count = 0;
    
	while (*str)
	{
		if (*str == '>')
			ptr++;
		else if (*str == '<')
			ptr--;
		else if (*str == '+')
			++(*ptr);
		else if (*str == '-')
			--(*ptr);
		else if (*str == '.')
			write(1, ptr, 1);
		else if (*str == '[' && *ptr == 0)
		{
			loop_count = 1;
			while (loop_count != 0)
			{
				str++;
				if (*str == ']')
					--loop_count;
				if (*str == '[')
					++loop_count;
			}
		}
		else if (*str == ']' && *ptr != 0)
		{
			loop_count = 1;
			while (loop_count != 0)
			{
				str--;
				if (*str == '[')
					--loop_count;
				if (*str == ']')
					++loop_count;
			}
		}
		str++;
	}
}

int		main(int argc, char *argv[])
{
	if (argc == 2)
		brainfuck(argv[1]);
	return (0);
}





#include <stdlib.h>
#include <stdio.h>

int my_len(long value, long base)
{
	int len;
	len = 0;
	if (value < 0 && base == 10)
	{
		value = -value;
		len++;
	}
	else if (value < 0)
	{
		value = -value;
	}
	while (value)
	{
		value = value / base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	long val = value;
	long ba = base;
	int o;
	int len;
	char buf[17] = "0123456789ABCDEF";
	char *str = NULL;

	// if (base > 16 || base < 4)
	// 	return (NULL);
	len = my_len(val, ba);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	if (val == 0)
	{
		str[0] = '0';
		return (str);
	}
	else if (val < 0 && ba == 10)
	{
		str[0] = '-';
		val *= -1;
	}
	else if (val < 0)
		val = -val;
	while (val)
	{
		o = val % ba;
		str[len] = buf[o];
		len--;
		val = val / ba;
	}
	return (str);
}

int main(int ac, char **av)
{
	char *str;
	if (ac > 2)
		str = ft_itoa_base(atoi(av[1]), atoi(av[2]));
	printf("print str : %s", str);
	return (0);
}