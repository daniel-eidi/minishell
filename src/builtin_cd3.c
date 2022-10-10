/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:43:02 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 16:52:32 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_many_args_msg(void)
{
	printf("cd: too many arguments\n");
	g_data->exit_code = 1;
	return ;
}
