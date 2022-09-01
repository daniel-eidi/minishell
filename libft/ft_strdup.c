/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2021/08/09 16:30:05 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief function copies n bytes from memory area src to
 *memory area dest.  The memory areas may overlap: copying takes
 * place as though the bytes in src are first copied into a
 * temporary array that does not overlap src or dest, and the bytes
 * are then copied from the temporary array to dest
 * 
 * @param dest 
 * @param src 
 * @param n 
 * @return void* 
 */
char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	len;
	char	*ori;

	ori = (char *) s;
	len = ft_strlen(s);
	new = (char *) malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, ori, len + 1);
	return (new);
}
