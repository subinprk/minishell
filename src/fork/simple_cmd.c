/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:07:25 by subpark           #+#    #+#             */
/*   Updated: 2024/02/08 17:24:00 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pipefd(int pipefd[2], int old_input, int pipe_exist)
{
	close(pipefd[0]);
	if (old_input != -1)
		(dup2(old_input, 0));
	if (pipe_exist == -1)
		close(pipefd[1]);
	else
		dup2(pipefd[1], 1);
}

void	write_pipefd(int pipefd[2], int *old_input, int pipe_exist)
{
	close(pipefd[1]);
	if (*old_input != -1)
		close(*old_input);
	if (pipe_exist == -1)
	{
		close(pipefd[0]);
		*old_input = -1;
	}
	else
		*old_input = pipefd[0];
}

void	update_redirfd(t_stdio *stdios)
{
	t_stdio	*last_in;
	t_stdio	*last_out;

	if (stdios == NULL)
		return ;
	last_in = find_last_in(stdios);
	last_out = find_last_out(stdios);
	if (last_in != NULL)
		connect_last_in(last_in);
	if (last_out != NULL)
		connect_last_out(last_out);
}
