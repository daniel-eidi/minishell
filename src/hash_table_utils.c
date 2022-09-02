#include <hash_table.h>

t_item	*new_item(char *new_key, char *new_value)
{
	t_item	*new;

	new = (t_item *) malloc(sizeof(t_item));
	new->key = new_key;
	new->value = new_value;
	return (new);
}

void	insert_item(t_item *item, t_list **table)
{
	int	ind;
	int	size;
	t_item	*aux;

	size = 0;
	while (table[size])
		++size;
	ind = get_hash(item->key) % size;
	if (((t_item *)table[ind]->content)->key == NULL)
	{
		aux = table[ind]->content;
		table[ind]->content = item;
		free(aux);
	}
	else
	{
		ft_lstadd_back(&table[ind], ft_lstnew(item));
	}
}

t_list	**hash_table_init(int size)
{
	t_list	**table;
	int 	i;

	table = (t_list **) malloc((size + 1) * (sizeof(t_list *)));
	table[size] = NULL;
	i = -1;
	while (++i < size)
		table[i] = ft_lstnew(new_item(NULL, NULL));
	return (table);
}

/*
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
*/
