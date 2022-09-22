/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:32:57 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/22 00:29:33 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<minishell.h>

static char	*get_var_value(char *key)
{
	t_list *temp;
	char *str_temp;
	
	str_temp = NULL;
	temp = find_entry(key, g_data->hash_table);
	if (temp == NULL)
		return("");
	str_temp = ft_strdup(((t_item *)temp->content)->value);
	return (str_temp);
}

void	update_hashtable(char *key, void *new_value, t_list	**hash_table)
{
	t_list *temp;
	t_item *item;
	//char *str_temp;
	
	//str_temp = NULL;
	//printf("update key %s to value %s\n", key, (char *)new_value);
	temp = find_entry(key, hash_table);
	if (temp == NULL)
		return;
	item = temp->content;
	printf("old value of key %s was %s\n", key, item->value);
	item->value = ft_strdup(new_value);
	//str_temp = ft_strdup(new_value);
	printf("new value of key %s is %s\n", key, item->value);
}

void	builtin_cd(t_list *cmd)
{
	t_list *aux;
	char *str_temp;
	char *absolute_path;
	
	aux = cmd->next;
	g_data->exit_code = 0;
	absolute_path = NULL;
	if (aux == NULL)
		absolute_path = get_var_value("HOME");
	else if (aux && aux->next)
	{
		printf("cd: too many arguments\n");
		g_data->exit_code = 1;
		return;
	}		
	else if (((char *)aux->content)[0] == '~' )
	{
		str_temp = get_var_value("HOME");
		absolute_path = ft_strjoin(str_temp, aux->content + 1);
		free_ptr((void *)&str_temp);
	}
	else if (((char *)aux->content)[0] == '/')
		absolute_path = aux->content;
	str_temp = get_var_value("PWD");
	printf("pwd_antes=%s\n", str_temp);
	update_hashtable("OLDPWD", str_temp, g_data->hash_table);
	update_hashtable("PWD", absolute_path, g_data->hash_table);
	printf("pwd_depois=%s\n", str_temp);
	free_ptr((void *)&str_temp);
	str_temp = get_var_value("PWD");
	free_ptr((void *)&absolute_path);
}
