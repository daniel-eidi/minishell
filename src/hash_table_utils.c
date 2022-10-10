/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:49:48 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 14:55:22 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	int		ind;
	t_item	*aux;

	ind = get_ind(item->key, table);
	if (((t_item *)table[ind]->content)->key == NULL)
	{
		aux = table[ind]->content;
		table[ind]->content = item;
		free(aux);
	}
	else
		ft_lstadd_back(&table[ind], ft_lstnew(item));
}

t_list	**hash_table_init(int size)
{
	t_list	**table;
	int		i;

	table = (t_list **) malloc((size + 1) * (sizeof(t_list *)));
	if (table)
	{
		table[size] = NULL;
		i = -1;
		while (++i < size)
			table[i] = ft_lstnew(new_item(NULL, NULL));
	}
	return (table);
}

t_list	*find_entry(char *searched_key, t_list **table)
{
	t_list	*aux;

	aux = table[get_ind(searched_key, table)];
	if (((t_item *)aux->content)->key == NULL)
		return (NULL);
	while (aux)
	{
		if (!ft_strcmp(((t_item *)aux->content)->key, searched_key))
			break ;
		aux = aux->next;
	}
	return (aux);
}

void	update_hashtable(char *key, void *new_value, t_list	**hash_table)
{
	t_list	*temp;
	t_item	*item;

	temp = find_entry(key, hash_table);
	if (temp == NULL)
		return ;
	item = temp->content;
	free_ptr((void *)&item->value);
	item->value = ft_strdup(new_value);
}
