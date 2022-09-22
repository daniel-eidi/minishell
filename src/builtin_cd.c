/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:32:57 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/22 14:13:34 by daeidi-h         ###   ########.fr       */
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
