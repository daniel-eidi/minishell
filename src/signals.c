/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:41:44 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/04 17:12:34 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void ctrlc_main(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		dprintf(2, "entrou no if na função ctrlc_main\n");	
		printf("\n");
		rl_replace_line("",0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_for_main(void)
{
	signal(SIGINT, ctrlc_main);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, ctrlc_main);
} 

static void ctrlc_child(int signal)
{
		dprintf(2, "entrou na função ctrlc_child\n");	
	(void)signal;
	if (signal == SIGQUIT)
		error("", 131);
	if (signal == SIGINT)
	{
		dprintf(2, "entrou no if do sigint\n");
		error("", 130);
	}
}

void	signal_for_child(void)
{
		dprintf(2, "entrou na signal for child\n");
	signal(SIGINT, ctrlc_child);
	signal(SIGQUIT, ctrlc_child);
	///signal(SIGTERM, SIGTERM);
}
