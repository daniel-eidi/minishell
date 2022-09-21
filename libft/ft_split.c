/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/02/28 21:25:33 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting ’s’ using the
 * character ’c’ as a delimiter. The array must be
 * ended by a NULL pointer.
 * 
 * @param s 
 * @param c 
 * @return char** 
 */

static void	ft_insertword(char const *s, char c, char **str)
{
	int			i;
	int			nstr;
	int			ini;

	i = 0;
	ini = -1;
	nstr = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && ini == -1)
		{
			ini = i;
		}
		if ((s[i + 1] == c && ini != -1) || (s[i + 1] == '\0' && ini != -1))
		{
			str[nstr] = ft_substr(s, ini, i - ini + 1);
			ini = -1;
			nstr++;
		}
		i++;
	}
	str[nstr] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char		**str;
	int			words;

	if (!s)
		return (NULL);
	words = ft_countword(s, c);
	str = (char **) malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	ft_insertword(s, c, str);
	return (str);
}
