/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_uatoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:10:53 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/18 15:46:49 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief convert to int.
 * 
 * @param str 
 * @return int 
 */
unsigned int	invalid_uatoi(const char *str)
{
	unsigned long long	nbr;
	int					sign;
	unsigned int		i;

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
	if (sign == -1)
		return (nbr - 1 > 9223372036854775807);
	else
		return (nbr > 9223372036854775807);
}
