/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:27 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/10 15:00:32 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned long	ft_pow(int base, int exp)
{
	unsigned long	result;

	result = 1;
	while (--exp >= 0)
		result *= base;
	return (result);
}
