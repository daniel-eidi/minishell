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
	t_item **hash_table;
	t_item	*item;

	ft_printf("get hash moacir = %d\n", get_hash("moacir"));
	hash_table = hash_table_init(10);
	item = new_item("XAR", "moacir");
	insert_item(item, hash_table);
	item = new_item("CAR", "golf");
	insert_item(item, hash_table);
	item = new_item("term", "linux");
	insert_item(item, hash_table);
	i = -1;
	while (hash_table[++i])
		if (hash_table[i]->key)
			printf("%s\n", hash_table[i]->key);
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
