/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_a_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:12:24 by subpark           #+#    #+#             */
/*   Updated: 2024/02/11 23:39:08 by ubuntu           ###   ########.fr       */
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

	/* int j = 0;
	while (chopped_str[j])
	{
		printf("chopped_str[%d]: %s\n", j, chopped_str[j]);
		j++;
	} */


	if (!chopped_str)
		return (NULL);
	token = token_data(chopped_str);
	if (!token)
		return (NULL);
	i[0] = 0;
	i[1] = token_length(token);
	tmp = syntax_pipe(chopped_str, token, i, &cmd_tree);
	if (tmp == -1)
	{
		free_tree(cmd_tree);
		return (NULL);
	}
	//printf("chopped_str: %s\n", cmd_tree->cmdstr[1]);
	free_2d(chopped_str);
	free(token);
	return (cmd_tree);
}

