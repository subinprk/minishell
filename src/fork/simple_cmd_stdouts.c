/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_stdouts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 01:07:41 by siun              #+#    #+#             */
/*   Updated: 2024/02/08 17:23:21 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	re_type_r_pipes(int filefd)
{
	int	fd_tmp;

	fd_tmp = dup2(filefd, 1);
	if (fd_tmp == -1)
	{
		close(filefd);
		exit(errno);
	}
}

void	connect_last_out(t_stdio *last_out)
{
	int	filefd;

	filefd = -1;
	if (last_out->re_type == REL_TYPE_R)
	{
		filefd = open(last_out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (filefd == -1)
			exit(errno);
		re_type_r_pipes(filefd);
	}
	else if (last_out->re_type == REL_TYPE_RR)
	{
		filefd = open(last_out->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (filefd == -1)
			exit(errno);
		re_type_r_pipes(filefd);
	}
	close(filefd);
}

t_stdio	*find_last_out(t_stdio *stdios)
{
	t_stdio	*last_out;
	t_stdio	*curr;

	last_out = NULL;
	curr = stdios;
	while (curr)
	{
		if (curr->re_type == REL_TYPE_R || curr->re_type == REL_TYPE_RR)
			last_out = curr;
		curr = curr->next_stdio;
	}
	return (last_out);
}
