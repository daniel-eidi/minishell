/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2021/08/20 14:30:21 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief function locates the	first occurrence of the	null-termi-
 * nated string little in the	string big, where not more than	len characters
 * are searched.  Characters that appear after a `\0'	character are not
 * searched.
 * 
 * @param s1 
 * @param s2 
 * @param len 
 * @return char If	little is an empty string, big is returned; if little
 * occurs nowhere in	big, NULL is returned; otherwise a pointer to the
 *  first	character of the first occurrence of little is returned
 */
char	*ft_strnstr(const char	*s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i < len)
	{
		j = 0;
		while (s2[j] != '\0' && s1[i + j] == s2[j] && (i + j) < len)
			j++;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
