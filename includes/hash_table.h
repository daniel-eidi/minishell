#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# ifndef P_PARAM
#  define P_PARAM 31
# endif

# ifndef M_PARAM
#  define M_PARAM 1000000007
# endif

# include <stddef.h>

typedef struct s_item
{
	char	*name;
	char	*content;
}	t_item;

int	ft_pow(int base, int exp);
size_t	ft_strlen(const char *s);

#endif
