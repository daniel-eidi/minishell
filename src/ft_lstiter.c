/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:54:21 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/27 03:13:40 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node_ptr;

	node_ptr = lst;
	while (node_ptr)
	{
		(*f)(node_ptr->content);
		node_ptr = node_ptr->next;
	}
}
