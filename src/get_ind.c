#include <hash_table.h>

int	get_hash(char *s)
{
	long	hash;
	int	i;
	int	len;
	char	a;

	len = ft_strlen(s);
	hash = 0;
	i = -1;
	while (++i < len)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			a = 'a';
		if (s[i] >= 'A' && s[i] <= 'Z')
			a = 'A';
		hash += (s[i] - a + 1) * ft_pow(P_PARAM, i);
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
