/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pids.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 23:09:07 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/29 16:20:17 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	*create_pids(int n_cmd)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * n_cmd);
	return (pid);
}