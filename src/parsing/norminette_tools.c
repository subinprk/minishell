/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:06:54 by subpark           #+#    #+#             */
/*   Updated: 2024/02/12 15:11:07 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_pipe_error_print(void)
{
	write(2, "syntax error near unexpected token '|'\n",
		ft_strlen("syntax error near unexpected token '|'\n"));
	g_exit_status = 1;
}

void	syntax_pipe_i_update(int *i, int pipe_index, int tmp)
{
	i[0] = pipe_index + 1;
	i[1] = tmp;
}
