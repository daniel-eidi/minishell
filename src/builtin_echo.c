/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:49:23 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/06 12:47:36 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_echo(char **cmd)
{
	char	*end_line;
	int		i;

	i = 1;
	end_line = "\n";
	if (!cmd[i])
	{
		ft_printf("%s", end_line);
		g_data->exit_code = 0;
		return ;
	}
	if (!ft_strcmp(cmd[i], "-n"))
	{
		end_line = "";
		i++;
	}
	ft_printf("%s", cmd[i++]);
	while (cmd[i])
		ft_printf(" %s", cmd[i++]);
	ft_printf("%s", end_line);
	g_data->exit_code = 0;
}
