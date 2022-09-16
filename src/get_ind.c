#include <hash_table.h>

int	get_hash(char *s)
{
	long	hash;
	int	i;
	int	len;

	len = ft_strlen(s);
	hash = 0;
	i = -1;
	while (++i < len)
	{
		hash += (s[i] + 1) * ft_pow(P_PARAM, i);
	}
	return (hash % M_PARAM);
}

int	get_ind(char *key, t_list **table)
{
	int	ind;
	int	size;

	size = 0;
	while (table[size])
		++size;
	ind = get_hash(key) % size;
	return (ind);
}
