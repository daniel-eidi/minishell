/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:51:56 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/27 03:13:18 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node_ptr;

	node_ptr = ft_lstlast(*lst);
	if (node_ptr)
		node_ptr->next = new;
	else
		*lst = new;
}
