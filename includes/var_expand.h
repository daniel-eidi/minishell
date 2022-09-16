/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:32:00 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/15 01:53:14 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPAND_H
# define VAR_EXPAND_H

typedef struct s_aux_expand
{
	char	*prev;
	char	*after;
	char	*var;
	char	*keyvar;
	char	*aux1;
	char	*aux2;
	int		dif1;
	int		dif2;
	int		dif3;
}	t_aux_expand;


#endif
