#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# ifndef P_PARAM
#  define P_PARAM 31
# endif

# ifndef M_PARAM
#  define M_PARAM 1000000007
# endif

# include <stddef.h>
# include <stdlib.h>

#include <stdio.h> //REMOVE!

typedef struct s_item
{
	char	*key;
	char	*value;
}	t_item;

int	ft_pow(int base, int exp);
size_t	ft_strlen(const char *s);
int	get_hash(char *s);
t_item	**hash_table_init(int size);
void	insert_item(t_item *item, t_item **table);
t_item	*new_item(char *new_key, char *new_value);

#endif
