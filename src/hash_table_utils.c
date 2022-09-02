#include <hash_table.h>

t_item	*new_item(char *new_key, char *new_value)
{
	t_item	*new;

	new = (t_item *) malloc(sizeof(t_item));
	new->key = new_key;
	new->value = new_value;
	return (new);
}

void	insert_item(t_item *item, t_item **table)
{
	int	ind;
	int	size;
	t_item	*aux;

	aux = *table;
	size = 0;
	while (table[size])
		++size;
	ind = get_hash(item->key) % size;
	while (table[ind])
	{
		if (table[ind]->key == NULL)
		{
			aux = table[ind];
			table[ind] = item;
			free(aux);
			return ;
		}
		else
		{
			ind++;
			ind %= size;
			printf("table[ind]->key = %s\n", table[ind]->key);
		}
	}
}

t_item	**hash_table_init(int size)
{
	t_item	**table;
	int 	i;

	table = (t_item **) malloc((size + 1) * (sizeof(t_item *)));
	table[size] = NULL;
	i = -1;
	while (++i < size)
		table[i] = new_item(NULL, NULL);
	return (table);
}
