#include <minishell.h>

int	get_var_ind(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == -2) && \
			(ft_isalpha(s[i + 1]) || (s[i + 1] == '_')))
			return (i);
	}
	return (-1);
}

char	*get_line_with_var_expanded(char *s, int ind, int end, t_list **table)
{
	char	*s2;
	char	*p;
	t_list	*aux;

	s2 = ft_substr(s, ind + 1, end - ind);
	aux = find_entry(s2, table);
	//free(s2);
	free_ptr((void *) &s2);
	if (aux == NULL)
		s2 = ft_strjoin("", s + end + 1);
	else
		s2 = ft_strjoin(((t_item *)aux->content)->value, s + end + 1);
	s[ind] = '\0';
	p = ft_strjoin(s, s2);
	//free(s);
	//free_ptr((void *) &s);
	//free(s2);
	free_ptr((void *) &s2);
	return (p);
}

char	*exp_var(char *line, t_list **table)
{
	int	ind;
	int	end;

	ind = get_var_ind(line);
	while(ind > -1)
	{
		end = ind + 1;
		while (ft_isalnum(line[end + 1]) || (line[end + 1] == '_'))
			end++;
		line = get_line_with_var_expanded(line, ind, end, table);
		ind = get_var_ind(line);
	}
	return (line);
}
