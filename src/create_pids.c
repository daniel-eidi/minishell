/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pids.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 23:09:07 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/10 10:41:57 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	*create_pids(int n_cmd)
{
	pid_t	*pid;
	int		i;

	pid = malloc(sizeof(pid_t) * n_cmd);
	i = -1;
	while (++i < n_cmd)
		pid[i] = 0;
	return (pid);
}
