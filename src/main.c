# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	static char	*line;
	char		*cmd;
	char		*temp;
	char		**split;
	int			i;
	(void)	argv;
	(void)	argc;
	(void)	envp;
	t_list **hash_table;
	t_item	*item;
	t_list	*aux;

	ft_printf("get hash moacir = %d\n", get_hash("moacir"));
	hash_table = hash_table_init(10);
	item = new_item("XAR", "moacir");
	insert_item(item, hash_table);
	item = new_item("CAR", "golf");
	insert_item(item, hash_table);
	item = new_item("term", "linux");
	insert_item(item, hash_table);
	item = new_item("derm", "linx");
	insert_item(item, hash_table);
	item = new_item("VAR", "lol");
	insert_item(item, hash_table);
	item = new_item("ARG", "cat");
	insert_item(item, hash_table);
	i = -1;
	while (hash_table[++i])
	{
		aux = hash_table[i];
		printf("i = %d, key = %s, value = %s\n", i, ((t_item *)aux->content)->key, ((t_item *)aux->content)->value);
		while (aux->next)
		{
		aux = aux->next;
		printf("i = %d, key = %s, value = %s\n", i, ((t_item *)aux->content)->key, ((t_item *)aux->content)->value);
		}
	}
	//	if (((t_item *)hash_table[i]->content)->key)
	//		printf("%s\n", ((t_item *)hash_table[i]->content)->key);
	i=0;
	line = "";
	while(ft_strncmp(line = readline("> "), "exit", 5))
	{
		i=0;
		if(ft_strlen(line) > 0)
			add_history(line);
		temp = treat_line(line);
		cmd = space_arg(temp, "<");
		ft_printf("comando com spaços - %s\n", cmd);
		split = ft_split(cmd, ' ');
		ft_printf("--	tentativa de tokens  --- \n");
		while(split[i])
			ft_printf("%s\n", split[i++]);
		free(line);
	}
	return(0);
}
