/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:26:09 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/12 17:55:26 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	var_expand(t_list *list)
{
	char *temp;

	temp = list->content;
	if (temp == '\'')
		return();
	if(temp == '\"')
		dif = ft_strchr(envp[i], '$') - envp[i];
		key = ft_substr(envp[i], 0, dif);
		value = ft_substr(envp[i], dif + 1, ft_strlen(envp[i]) - dif);
}