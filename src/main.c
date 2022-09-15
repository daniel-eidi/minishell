# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

t_data	*data;

int main(int argc, char **argv, char **envp)
{
	static char	*line;
//	char		*cmd;
//	char		*temp;
	char		**token;
	int			i;
	(void)	argv;
	(void)	argc;
	(void)	envp;
	//t_list	*item;
	t_list	**aux;
	t_list	*aux2;
	t_list	*aux3;
	t_list	*aux4;
	char *teste;

//	i=0;
	data = init_data();
	hash_envp(data, envp);
	//item = find_entry("PW", data->hash_table);
	//printf("PWD = %s\n",((t_item *)item->content)->value);
	teste = mult_var_expand("gjga$OLDPWD$PWD$PWD", data->hash_table);
	printf("expansão = %s\n", teste);
	line = "";
	while(ft_strncmp(line = readline("> "), "exit", 5))
	{
//		i=0;
		if(ft_strlen(line) > 0)
			add_history(line);
		//temp = treat_line(line);
		//cmd = space_arg(temp, "<");
		//ft_printf("comando com spaços - %s\n", cmd);
		token = token_line(line);
		//ft_printf("--	tentativa de tokens  --- \n");
		//while(split[i])
		//	ft_printf("%s\n", split[i++]);
		aux = make_cmd_table(token);
		
		i = 1;
		while ((*aux))
		{
			printf("command #%d\n", i);
			aux2 = (t_list *) ((t_cmd *)(*aux)->content)->cmd;
			while (aux2)
			{
			printf("command = %s\n", (char *)aux2->content);
			aux2 = aux2->next;
			}
			aux3 = (t_list *) ((t_cmd *)(*aux)->content)->outfiles;
			while (aux3)
			{
			printf("outfile = %s\n", (char *)aux3->content);
			aux3 = aux3->next;
			}
			aux4 = (t_list *) ((t_cmd *)(*aux)->content)->infiles;
			while (aux4)
			{
			printf("infile = %s\n", (char *)aux4->content);
			aux4 = aux4->next;
			}
			*aux = (*aux)->next;
			++i;
		}
		
		clear_cmd_table(aux);
		i = -1;
		while (token[++i])
			free(token[i]);
		//	printf("split[%d] = %s\n", i, split[i]);
		free(token);
		free(line);
	}
	return(0);
}
