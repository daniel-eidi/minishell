/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:07:05 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/13 12:36:31 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_special_string(char *aux_i)
{
	char	**tokens;
	int		i;
	int		r;

	tokens = (char **) malloc(6 * sizeof(char *));
	tokens[0] = "<";
	tokens[1] = ">";
	tokens[2] = "<<";
	tokens[3] = ">>";
	tokens[4] = "|";
	tokens[5] = NULL;
	r = 0;
	i = -1;
	while (tokens[++i])
	{
		if (!ft_strcmp(aux_i, tokens[i]))
			r = 1;
	}
	free_ptr((void *)&tokens);
	return (r);
}

int	not_null(char *aux_i, int *r)
{
	if (!aux_i)
		return (0);
	if (is_special_string(aux_i))
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, aux_i, ft_strlen(aux_i));
		write(2, "'\n", 2);
		*r = 1;
	}
	return (1);
}

int	invalid_syntax_redir(char *str)
{
	int		i;
	char	**aux;
	int		r;

	aux = ft_split(str, ' ');
	r = 0;
	i = -1;
	while (aux[++i])
	{
		if (is_special_string(aux[i]))
		{
			if (not_null(aux[++i], &r))
				break ;
			else
			{
				write(2, "syntax error near unexpected token `newline'\n", 45);
				r = 1;
				break ;
			}
		}		
	}
	free_split((void **)aux);
	free_ptr((void *)&aux);
	return (r);
}
