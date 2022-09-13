/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:26:09 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/13 14:07:48 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	var_expand(t_list *list, t_data *data)
{
	t_list	*temp;
	t_list	*new;
	t_list	*aux_next;
	char	*prev;
	char	*after;
	int		dif;
	int		count;

	temp = list;
	count = ft_countword(temp->content, '$');
	//ft_printf("qtd de $ = %d \n", count);
	if (*(char *)temp->content == '\'' && count == 0)
		return;
	while (count > 1)
	{
		aux_next = temp->next;
		dif = (void *)ft_strchr(temp->content, '$') - temp->content;
		prev = ft_substr(temp->content, 0, dif);
		after = ft_substr(temp->content, dif + 1, (void *)ft_strchr(temp->content + dif, '$') - temp->content);
		temp->content = prev;
		new = find_entry(after, data->hash_table);
		new = ft_lstnew(new->content);
		temp->next = new;
		new->next = aux_next;
		temp = new;
		
	} ///parei aqui
	aux_next = temp->next;
	dif = (void *)ft_strchr(temp->content, '$') - temp->content;
	//ft_printf("valor dif = %d \n", dif);
	prev = NULL;
	if (dif > 0)
		prev = ft_substr(temp->content, 0, dif);
	//ft_printf("prev= %s \n", prev);
	after = ft_substr(temp->content, dif + 1, (void *)ft_strchr(temp->content + dif, '\0') - temp->content);
	//ft_printf("after= %s \n", after);
	if (prev )
	{
		//ft_printf("tem prev \n");
		temp->content = prev;
		new = find_entry(after, data->hash_table);
		new = ft_lstnew(new->content);
		temp->next = new;
		new->next = aux_next;
		temp = new;		
	}
	else 
	{
		ft_printf("after = %s\n", after);
		new = find_entry(after, data->hash_table);
		temp->content = ((t_item *)new->content)->value;
		ft_printf("new->content = %s \n", temp->content);
	}
}
