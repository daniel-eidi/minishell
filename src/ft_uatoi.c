/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uatoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:10:53 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/18 09:11:52 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief convert to int.
 * 
 * @param str 
 * @return int 
 */
unsigned int	ft_uatoi(const char *str)
{
	unsigned int	nbr;
	unsigned long	sign;
	unsigned int	i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' \
	|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit((int) str[i]))
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return ((unsigned int)(nbr * sign));
}
