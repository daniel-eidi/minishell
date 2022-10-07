/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:52:02 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/07 04:30:50 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_pwd(void)
{
	t_list	*temp;

	temp = find_entry("PWD", g_data->hash_table);
	if (temp == NULL)
		g_data->exit_code = 1;
	else
	{
		printf("%s\n", ((t_item *)temp->content)->value);
		g_data->exit_code = 0;
	}
	exit (0);
}
