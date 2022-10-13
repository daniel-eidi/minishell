/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:08:13 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/13 10:29:28 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env(void)
{
	t_list	*aux;
	int		i;

	i = -1;
	while (g_data->hash_table[++i])
	{
		aux = (g_data->hash_table[i]);
		while (aux)
		{
			if (((t_item *) aux->content)->key != NULL)
				ft_printf("%s=%s\n", ((t_item *) aux->content)->key, \
					((t_item *) aux->content)->value);
			aux = aux->next;
		}
	}
	g_data->exit_code = 0;
}

void	unset_cmd(char *var_name)
{
	t_list	*aux;

	aux = find_entry(var_name, g_data->hash_table);
	if (aux)
		delete_entry(var_name, g_data->hash_table);
}

void	builtin_unset(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
		unset_cmd(cmd[i]);
}
