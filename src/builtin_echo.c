/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:49:23 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/07 04:31:36 by daeidi-h         ###   ########.fr       */
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
	exit(0);
}
