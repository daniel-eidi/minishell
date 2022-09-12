/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 23:13:53 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/12 15:26:17 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	hash_envp(t_data *data, char **envp)
{
	int		i;
	char 	*key;
	char	*value;
	int		dif;
	t_item	*item;
	t_list	*aux;
	(void) envp;
	
	item = new_item("TESTE fsfsdfs. sdf grande", "value tadfsdfsdfsdmbem grande");
	insert_item(item, data->hash_table);
		
	i = 0;
	while(envp[i])
	{
		dif = ft_strchr(envp[i], '=') - envp[i];
		key = ft_substr(envp[i], 0, dif);
		value = ft_substr(envp[i], dif + 1, ft_strlen(envp[i]) - dif);
		ft_printf("key = %s\n", key);
		ft_printf("value = %s\n", value);
		ft_printf("envp = %s\n", envp[i]);
		item = new_item(key, value);
		printf("item->key = %s\n", item->key);
		insert_item(item, data->hash_table);
		//free_ptr((void *)&data->hash_table);
		free(value);
		//free(item->key);
		//free(item->value);
		free(key);
		i++;
	}

	i = -1;
	while (data->hash_table[++i])
	{
		aux = data->hash_table[i];
		printf("i = %d, key = %s, value = %s\n", i, ((t_item *)aux->content)->key, ((t_item *)aux->content)->value);
		while (aux->next)
		{
		aux = aux->next;
		printf("i = %d, key = %s, value = %s\n", i, ((t_item *)aux->content)->key, ((t_item *)aux->content)->value);
		}
		
	}
}
