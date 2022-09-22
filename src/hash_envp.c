/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 23:13:53 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/21 21:54:08 by daeidi-h         ###   ########.fr       */
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

void	builtin_env(t_data *data)
{
	int	j;
	t_list	*aux;
	
	j = -1;
	while (data->hash_table[++j])
	{
		aux = data->hash_table[j];
		printf("%s=%s\n", ((t_item *)aux->content)->key, ((t_item *)aux->content)->value);
		while (aux->next)
		{
		aux = aux->next;
		printf("%s=%s\n", ((t_item *)aux->content)->key, ((t_item *)aux->content)->value);
		}		
	}
}
