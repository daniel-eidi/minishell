/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:26:09 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/13 14:07:48 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

static char *one_var_expand(char *temp, t_list **hash_table)
{
	t_list	*new;
	char	*prev;
	char	*var;
	char	*keyvar;
	char	*aux1;
	int		dif1;
	int		dif2;


	dif1 = ft_strchr(temp, '$') - temp;
	prev = ft_substr(temp, 0, dif1);
	dif2 = ft_strchr(temp, '\0') - temp;
	keyvar = ft_substr(temp, dif1 + 1, dif2);
	new = find_entry(keyvar, hash_table);
	var = ((t_item *)new->content)->value;
	aux1 = ft_strjoin(prev, var);
	free_ptr((void *)prev);
	free_ptr((void *)keyvar);
	return(aux1);
}


static char *var_expand(char *temp, t_list **hash_table)
{
	t_list	*new;
	char	*prev;
	char	*var;
	char	*keyvar;
	char	*after;
	char	*aux1;
	char	*aux2;
	int		dif1;
	int		dif2;
	int		dif3;


	dif1 = ft_strchr(temp, '$') - temp;
	prev = ft_substr(temp, 0, dif1);
	dif2 = ft_strchr(temp + dif1 + 1, '$') - temp - 1;
	keyvar = ft_substr(temp, dif1 + 1, dif2);
	dif3 = ft_strchr(temp + dif2, '\0') - temp;
	after = ft_substr(temp, dif2 + 1, dif3);
	new = find_entry(keyvar, hash_table);
	var = ((t_item *)new->content)->value;
	aux1 = ft_strjoin(prev, var);
	aux2 = aux1;
	aux1 = ft_strjoin(aux2, after);
	free_ptr((void *)&aux2);
	free_ptr((void *)&prev);
	free_ptr((void *)&keyvar);
	free_ptr((void *)&after);
	return(aux1);
}


char *mult_var_expand(char *arg, t_list **hash_table)
{
	char	*temp;
	char	*aux;
	int		count;
	(void)hash_table;

	temp = arg;
	count = ft_countword(temp, '$');
	if (count == 0)
		return(arg);
	while (count > 1)
	{
		aux = var_expand(temp, hash_table);
		free_ptr((void *)&temp);
		temp = aux;
		count--;
	}
	aux = one_var_expand(temp, hash_table);
	free_ptr((void *)&temp);
	temp = aux;
	return(temp);
}
