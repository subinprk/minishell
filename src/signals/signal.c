/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:48:47 by subpark           #+#    #+#             */
/*   Updated: 2024/02/08 17:00:10 by siun             ###   ########.fr       */
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

void	signal_reset_prompt(int signal)
{
	(void)signal;
	printf("\n");
	print_prompt();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_parent_handle(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
}

void	set_signals_interactive(pid_t pid)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	if (pid <= 0)
		sigaction(SIGINT, &act, NULL);
	else
		signal_parent_handle();
}
