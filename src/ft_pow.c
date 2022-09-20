#include <minishell.h>

unsigned long	ft_pow(int base, int exp)
{
	unsigned long	result;

	result = 1;
	while (--exp >= 0)
		result *= base;
	return (result);
}
