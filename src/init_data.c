/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:22:39 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/07 15:35:02 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

t_data *init_data(void)
{
	t_data	*g_data;

	g_data = (t_data *)ft_calloc(sizeof(t_data), 1);
	g_data->hash_table = hash_table_init(20);
	g_data->aux = malloc(sizeof(t_pids_pipes));
	return (g_data);
}
