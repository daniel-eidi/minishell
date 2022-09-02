/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:54:40 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/27 03:13:45 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*node_ptr;

	if (!lst)
		return (0);
	node_ptr = lst;
	while (node_ptr->next)
	{
		node_ptr = node_ptr->next;
	}
	return (node_ptr);
}
