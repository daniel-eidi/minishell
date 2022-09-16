/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:55:31 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/15 02:02:30 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_aux_expand	*init_aux_expand(void)
{
	t_aux_expand	*aux;

	aux = (t_aux_expand *)ft_calloc(sizeof(t_aux_expand), 1);
	aux->prev = NULL;
	aux->after = NULL;
	aux->var = NULL;
	aux->aux1 = NULL;
	aux->aux2 = NULL;
	aux->keyvar = NULL;
	aux->dif3 = 0;
	aux->dif1 = 0;
	aux->dif2 = 0;
	return (aux);
}
