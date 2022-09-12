/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:22:39 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/08 23:59:58 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

t_data *init_data(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	data->hash_table = hash_table_init(20);
	return (data);
}
