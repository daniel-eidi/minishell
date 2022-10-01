/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:41:44 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/01 20:20:13 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void ctrlc_main(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
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
	(void)signal;
	if (signal == SIGQUIT)
		error("", 131);
	if (signal == SIGINT)
		error("", 130);		
}

void	signal_for_child(void)
{
	signal(SIGINT, ctrlc_child);
	signal(SIGQUIT, ctrlc_child);
}
