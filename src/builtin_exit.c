/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:45:16 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/04 14:06:49 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exit_minishell(char **cmd)
{
	printf("exit\n");
	if (cmd && (cmd[2]))
	{
		write(2, "exit : too many arguments\n", 26);
		g_data->exit_code = 1;
		return ;
	}
	if (!cmd)
		exit(0);
	clear_table(g_data->hash_table);
	free(g_data);
	rl_clear_history();
	if (!cmd[1])
		exit (0);
	else
		exit(ft_atoi(cmd[1]));
}