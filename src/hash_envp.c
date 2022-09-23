/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 23:13:53 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/22 23:35:58 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

int	get_dif(char *s)
{
	int	dif;
	
	dif = 0;
	while ((s[dif]) && (s[dif] != '='))
		dif++;
	return (dif);
}

void	hash_envp(t_data *g_data, char **envp)
{
	int		i;
	char 	*key;
	char	*value;
	int		dif;
	t_item	*item;
			
	i = 0;	
	while (envp[i])
	{
		dif = get_dif(envp[i]);
		key = ft_substr(envp[i], 0, dif);
		value = ft_substr(envp[i], dif + 1, ft_strlen(envp[i]) - dif);
		item = new_item(key, value);
		insert_item(item, g_data->hash_table);
		i++;
	}
}
