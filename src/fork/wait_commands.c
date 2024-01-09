/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:41:27 by subpark           #+#    #+#             */
/*   Updated: 2024/01/09 17:51:18 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_cmd *tree)
{
	int count;

	if (tree == NULL)
		return (0);
	count = 0;

	if (tree->node_type == NODE_SIMPLE_CMD)
		count ++;
	count = count + count_commands(tree->left_child);
	count = count + count_commands(tree->right_child);

	return (count);
}

void	wait_each_commands(t_cmd *tree)
{
	int	num_commands;
	int	i;

	num_commands = count_commands(tree);
	i = 0;
	while (i < num_commands)
	{
		waitpid(-1, &g_exit_status, WUNTRACED);
		i ++;
	}
}