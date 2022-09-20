#include <minishell.h>

t_cmd	*get_cmd(int first, int last, char **words)
{
	t_cmd	*new;
	int	i;

	new = (t_cmd *) malloc(sizeof(t_cmd));
	new->cmd = NULL;
	new->infiles = NULL;
	new->outfiles = NULL;
	new->errfile = NULL;
	i = first;
	while (i < last)
	{
		if (!ft_strcmp(words[i], ">") || !ft_strcmp(words[i], ">>"))
			ft_lstadd_back(&new->outfiles, \
				ft_lstnew(ft_strdup(words[++i])));
		else if (!ft_strcmp(words[i], "<") || \
			!ft_strcmp(words[i], "<<"))
			ft_lstadd_back(&new->infiles, \
				ft_lstnew(ft_strdup(words[++i])));
		else
			ft_lstadd_back(&new->cmd, \
				ft_lstnew(ft_strdup(words[i])));
		i++;
	}
	return (new);
}

void	clear_cmd(t_cmd *cmd_deleted)
{
	ft_lstclear(&cmd_deleted->cmd, free);
	ft_lstclear(&cmd_deleted->infiles, free);
	ft_lstclear(&cmd_deleted->outfiles, free);
	free(cmd_deleted->errfile);
	free(cmd_deleted);
}

void	clear_cmd_table(t_list **cmd_table)
{
	t_list	*aux;
	t_list	*tp;

	aux = *cmd_table;
	while (aux)
	{
		clear_cmd(aux->content);
		tp = aux;
		aux = aux->next;
		free(tp);
	}
	free(cmd_table);
}

t_list	**make_cmd_table(char **words)
{
	t_list	**table;
	int	i;
	int	first;
	int	last;
	t_cmd	*new_cmd;

	if (words == NULL)
		return (NULL);
	table = (t_list **) malloc(sizeof(t_list *));
	*table = NULL;
	first = 0;
	i = -1;
	while (words[++i])
	{
		if ((words[i + 1] == NULL) || !ft_strcmp(words[i + 1], "|"))
		{
			last = i + 1;
			new_cmd = get_cmd(first, last, words);
			ft_lstadd_back(table, ft_lstnew(new_cmd));
			if (words[i + 1] != NULL)
				first = i + 2;
		}
	}
	return (table);
}
