/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:48:47 by subpark           #+#    #+#             */
/*   Updated: 2024/01/12 16:31:49 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
	//have to be discussed
}

void	signal_reset_prompt(int signal)
{
	(void)signal;
	printf("\n");
	print_prompt();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

// void	hered