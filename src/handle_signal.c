/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:23:06 by irivero-          #+#    #+#             */
/*   Updated: 2023/12/13 16:18:40 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.*/
void    handle_signal(int sign)
{
	pid_t	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);
    if (sign == SIGINT)
    {
		if (pid == -1)
        {
			ft_putstr_fd("\n", 1);
			generate_prompt();
			g_exit_status = 1;;
    	}
		else
			ft_putstr_fd("\n", 1);
	}
	else if (sign == SIGQUIT)
	{
		if (pid == -1)
			ft_putstr_fd("\b\b	\b\b", 1);
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}