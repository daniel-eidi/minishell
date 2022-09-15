/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:26:09 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/15 02:07:39 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	str_break(char *str, t_aux_expand *aux)
{	
	aux->dif1 = (ft_strchr(str, '$') - str);
	if (!ft_strchr(str + aux->dif1 + 1, '$'))
		aux->dif2 = aux->dif1;
	else
		aux->dif2 = ft_strchr(str + aux->dif1 + 1, '$') - str;
	aux->dif3 = ft_strchr(str + aux->dif2 + 1, '\0') - str;
	aux->prev = ft_substr(str, 0, aux->dif1);
	aux->after = ft_substr(str, aux->dif2, aux->dif3 - aux->dif2);
}

static char	*last_var_expand(char *temp, t_list **hash_table, t_aux_expand *aux)
{
	t_list	*new;

	str_break(temp, aux);
	aux->keyvar = ft_substr(temp, aux->dif2 + 1, aux->dif3 - aux->dif2 + 1);
	new = find_entry(aux->keyvar, hash_table);
	if (new == NULL)
		aux->var = "";
	aux->var = ((t_item *)new->content)->value;
	aux->aux1 = ft_strjoin(aux->prev, aux->var);
	free_ptr((void *)aux->prev);
	free_ptr((void *)aux->keyvar);
	free_ptr((void *)aux->var);
	return (aux->aux1);
}

static char	*var_expand(char *temp, t_list **hash_table, t_aux_expand *aux)
{
	t_list	*new;

	str_break(temp, aux);
	aux->keyvar = ft_substr(temp, aux->dif1 + 1, aux->dif2 - (aux->dif1 +1));
	new = find_entry(aux->keyvar, hash_table);
	if (new == NULL)
		aux->var = "";
	aux->var = ((t_item *)new->content)->value;
	aux->aux1 = ft_strjoin(aux->prev, aux->var);
	aux->aux2 = aux->aux1;
	aux->aux1 = ft_strjoin(aux->aux2, aux->after);
	free_ptr((void *)&aux->aux2);
	free_ptr((void *)&aux->prev);
	free_ptr((void *)&aux->var);
	free_ptr((void *)&aux->keyvar);
	free_ptr((void *)&aux->after);
	return (aux->aux1);
}

static int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*mult_var_expand(char *arg, t_list **hash_table)
{
	char			*temp;
	char			*temp2;
	int				count;
	t_aux_expand	*aux;

	aux = init_aux_expand();
	temp = arg;
	count = count_char(temp, '$');
	if (count == 0)
		return (arg);
	while (count > 1)
	{
		temp2 = var_expand(temp, hash_table, aux);
		free_ptr((void *)&temp);
		temp = temp2;
		count--;
	}
	temp2 = last_var_expand(temp, hash_table, aux);
	free_ptr((void *)&temp);
	temp = temp2;
	return (temp);
}
