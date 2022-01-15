#include "minishell.h"

/* Returns 1 if string 'str' only contains digits, 0 otherwise. */
int	ft_isdigit_str(const char *str)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}
