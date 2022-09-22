/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:49:23 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/22 23:40:56 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_echo(t_list *cmd)
{
	t_list	*aux;
	char	*end_line;

	aux = cmd->next;
	end_line = "\n";
	if (!aux)
		return ;
	if (!ft_strcmp(aux->content, "-n"))
	{
		end_line = "";
		aux = aux->next;
	}
	while (aux)
	{
		if (aux->next)
			ft_printf("%s ", aux->content);
		else
			ft_printf("%s", aux->content);
		aux = aux->next;
	}
	ft_printf("%s", end_line);
	g_data->exit_code = 0;
}
