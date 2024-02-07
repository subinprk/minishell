/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:48:01 by subpark           #+#    #+#             */
/*   Updated: 2024/02/07 08:06:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_prompt(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s", cwd);
}

void	interactive_mode(t_cmd **tree, char **envp, t_envp *env)
{
	char	*tmp;
	env->cd_hist = NULL;

	while (1)
	{
		set_signals_interactive(-1);
		print_prompt();
		tmp = readline(" ");
		add_history(tmp);
		if (!tmp)
			exit(0);//have to add some exiting things
		*tree = extract_command(tmp, env);
		search_tree(*tree, envp, env);
		printf("exit status %d\n", g_exit_status);
		write(1,"\0",1);
		wait_each_commands(*tree);
		free_tree(*tree);
		free(tmp);
	}
}

void	non_interactive_mode(t_cmd **tree, char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	//if (!user_inputs)
	//	exit_shell();
	i = 0;
	while (user_inputs[i])
	{
		*tree = extract_command(user_inputs[i], env);
		search_tree(*tree, envp, env);
		i ++;
		free_tree(*tree);
	}
	free_2d(user_inputs);
}

int main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;
	t_envp	env;
	char	**envp;

	env.envp = envs;
	(void)argc;
	envp = paths_array(envs);
	if (argc == 2)
		non_interactive_mode(&tree, argv[1], envp, &env);
	else if (isatty(STDIN_FILENO))
		interactive_mode(&tree, envp, &env);
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
