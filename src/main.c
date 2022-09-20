# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	static char	*line;
//	char		*cmd;
//	char		*temp;
	char		**split;
	int			i;
	(void)	argv;
	(void)	argc;
	(void)	envp;
	t_list **hash_table;
	t_item	*item;
	t_list	*aux;
	t_list	**aux_cmd;
	t_list	*aux2;
	t_list	*aux3;
	t_list	*aux4;

//	ft_printf("get hash moacir = %d\n", get_ind("moacir"));
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
	//aux = find_entry("ARG", hash_table);
	//printf("value of entry found = %s\n", ((t_item *)aux->content)->value);
	//	if (((t_item *)hash_table[i]->content)->key)
	//		printf("%s\n", ((t_item *)hash_table[i]->content)->key);
	
	i=0;
	line = "";
	while(ft_strncmp(line = readline("> "), "exit", 5))
	{
		i=0;
		if(ft_strlen(line) > 0)
			add_history(line);
		process_quotes(line);
		printf("line depois do process_quotes = %s\n", line);
		//line = exp_var(line, hash_table);
		printf("line expandida = %s\n", line);
//		temp = treat_line(line);
//		cmd = space_arg(temp, "<");
//		ft_printf("comando com spaços - %s\n", cmd);
		split = ft_split(line, ' ');
		ft_printf("--	tentativa de tokens  --- \n");
		aux_cmd = make_cmd_table(split);
		i = 1;
		while ((*aux_cmd))
		{
			printf("command #%d\n", i);
			aux2 = (t_list *) ((t_cmd *)(*aux_cmd)->content)->cmd;
			while (aux2)
			{
			printf("command = %s\n", (char *)aux2->content);
			aux2 = aux2->next;
			}
			aux3 = (t_list *) ((t_cmd *)(*aux_cmd)->content)->outfiles;
			while (aux3)
			{
			printf("outfile = %s\n", (char *)aux3->content);
			aux3 = aux3->next;
			}
			aux4 = (t_list *) ((t_cmd *)(*aux_cmd)->content)->infiles;
			while (aux4)
			{
			printf("infile = %s\n", (char *)aux4->content);
			aux4 = aux4->next;
			}
			*aux_cmd = (*aux_cmd)->next;
			++i;
		}
		
		clear_cmd_table(aux_cmd);
		i = -1;
		while (split[++i])
			free(split[i]);
		
		//while(line[i])
		//	ft_printf("%s\n", line[i++]);
		free(split);
		free(line);
	}
	clear_table(hash_table);
	
	return(0);
}
