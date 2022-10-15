/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:22:39 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/15 11:47:39 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*init_data(void)
{
	t_data	*g_data;

	g_data = (t_data *)ft_calloc(sizeof(t_data), 1);
	g_data->hash_table = hash_table_init(20);
	g_data->aux = NULL;
	g_data->not_run = 0;
	return (g_data);
}
