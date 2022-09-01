#include <minishell.h>

int	ft_pow(int base, int exp)
{
	int	result;

	result = 1;
	while (--exp >= 0)
		result *= base;
	return (result);
}
