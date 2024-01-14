/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_a_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:12:24 by subpark           #+#    #+#             */
/*   Updated: 2024/01/14 06:05:43 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//redirector, pipe, will be in other lexicon

#include "../../include/minishell.h"

t_cmd	*extract_command(char *str, t_envp *env)
{
	t_cmd	*cmd_tree;
	char	**chopped_str;
	int		*token;
	int		i[2];
	int		tmp;

	if (str == NULL || str[0] == 0)
		return (NULL);
	cmd_tree = NULL;
	chopped_str = input_validation(str, env->envp);
	replace_exit_status(&chopped_str);
	if (!chopped_str)
		return (NULL);
	token = token_data(chopped_str);
	if (!token)
		return (NULL);
	//function that parsing token & generate cmd linked list
	i[0] = 0;
	i[1] = token_length(token);
	tmp = syntax_pipe(chopped_str, token, i, &cmd_tree);
	if (tmp == -1)
	{
		free_tree(cmd_tree);
		return(NULL);
	}
	free_2d(chopped_str);
	free(token);
	return (cmd_tree);
}
