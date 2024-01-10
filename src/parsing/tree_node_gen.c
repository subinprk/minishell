/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node_gen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:52:28 by siun              #+#    #+#             */
/*   Updated: 2024/01/10 14:27:10 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*generate_tree_node(int node_type, int pipe_e)
{
	t_cmd *new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = node_type;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	new_node->cmdstr = NULL;
	new_node->pipe_exist = pipe_e;
	return (new_node);
}

t_cmd	*generate_end_node(char **line, int node_type, int start, int end)
{
	t_cmd *new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = node_type;
	new_node->left_child = NULL;
	new_node->right_child = NULL;
	if ((node_type == NODE_FILE_PATH || node_type == NODE_ARGV)
		&& (line[start][0] == '<' || line[start][0] == '>'))
		new_node->cmdstr = NULL;
	new_node->cmdstr = text_array_part_cpy(line, start, end);
	new_node->pipe_exist = -1;
	return (new_node);
}
