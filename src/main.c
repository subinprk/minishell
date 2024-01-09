/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:48:01 by subpark           #+#    #+#             */
/*   Updated: 2024/01/09 17:52:23 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_prompt()
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s", cwd);
}

void	interactive_mode(t_cmd **tree, char **envp)
{
	char	*tmp;

	while (1)
	{
		set_signals_interactive();
		print_prompt();
		tmp = readline(" ");
		if (!tmp)
			exit(0);//have to add some exiting things
		*tree = extract_command(tmp);
		search_tree(*tree, envp);
		printf("exit status %d\n", g_exit_status);
		write(1,"\0",1);
		wait_each_commands(*tree);
		free_tree(*tree);
		free(tmp);
	}
}

void	non_interactive_mode(t_cmd **tree, char *input, char **envp)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	//if (!user_inputs)
	//	exit_shell();
	i = 0;
	while (user_inputs[i])
	{
		*tree = extract_command(user_inputs[i]);
		search_tree(*tree, envp);
		i ++;
		free_tree(*tree);
	}
	free_2d(user_inputs);
}

int main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;
	char	**envp;

	(void)argc;
	envp = paths_array(envs);
	if (argc == 2)
		non_interactive_mode(&tree, argv[1], envp);
	else if (isatty(STDIN_FILENO))
		interactive_mode(&tree, envp);
	free_2d(envp);
	//exit_shell();
}
/*
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

	while(argc && argv[0] != NULL i < 5)
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
}*/