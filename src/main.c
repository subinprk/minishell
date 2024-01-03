/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:48:01 by subpark           #+#    #+#             */
/*   Updated: 2023/12/13 15:43:03 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envs)
{
//	char	**line;
	int		index, i;
	char	*tmp;
	char	**envp;
	t_cmd	*tree;

//	line = NULL;
	if (argc && argv)

//subin: should be initialised as a function for norminette later
	i = 0;
	index = 0;
	g_envp = cpy_full_2d_array(envs);
	envp = paths_array(envs);
	set_signal();

	while(/*argc && argv[0] != NULL*/ i < 5)
	{
		//get_line(line);
		//tree = extract_command(line[index]);
		generate_prompt();
		tmp = readline(" ");
		tree = extract_command(tmp);
		search_tree(tree, envp);
		index ++;
		free(tmp);
		free_tree(tree);
		i++;
	}
//also freeing shoud be in different function
	free_2d(envp);
	free_2d(g_envp);
	exit(g_exit_status);
}