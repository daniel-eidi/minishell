# include <minishell.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

t_data	*data;

int main(int argc, char **argv, char **envp)
{
	(void)	argv;
	(void)	argc;
	(void)	envp;

	char *teste;
	data = init_data();
	hash_envp(data, envp);
	teste = mult_var_expand("gjga$OLDPWD$PWD$PWD", data->hash_table);
	printf("expansão = %s\n", teste);
	free_ptr((void *) &teste);
	clear_table(data->hash_table);
	free(data);
	return(0);
}
