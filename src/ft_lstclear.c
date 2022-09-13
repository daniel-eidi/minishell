/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:52:53 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/27 03:13:31 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node_ptr;
	t_list	*aux;

	node_ptr = *lst;
	while (node_ptr->next)
	{
		(*del)(node_ptr->content);
		node_ptr->content = NULL;
		aux = node_ptr;
		node_ptr = node_ptr->next;
		free(aux);
	}
	(*del)(node_ptr->content);
	node_ptr->content = NULL;
	free(node_ptr);
	*lst = NULL;
}
