/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:53:09 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 14:53:52 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_item(void *item)
{
	t_item	*del_item;

	del_item = (t_item *) item;
	free(del_item->key);
	free(del_item->value);
	free(del_item);
}

void	delete_entry(char *searched_key, t_list **table)
{
	t_list	*aux;
	t_list	*aux_prev;

	aux = table[get_ind(searched_key, table)];
	aux_prev = NULL;
	while (aux)
	{
		if (!ft_strcmp(((t_item *)aux->content)->key, searched_key))
			break ;
		aux_prev = aux;
		aux = aux->next;
	}
	if (aux_prev)
	{
		aux_prev->next = aux->next;
		clear_item(aux->content);
		free(aux);
	}
	else
	{
		((t_item *)(aux->content))->key = NULL;
		((t_item *)(aux->content))->value = NULL;
	}
}

void	clear_table(t_list **table)
{
	int	i;

	i = -1;
	while (table[++i])
		ft_lstclear(&table[i], clear_item);
	free(table);
}
