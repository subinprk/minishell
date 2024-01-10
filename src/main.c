/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:48:01 by subpark           #+#    #+#             */
/*   Updated: 2024/01/10 19:27:42 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_prompt(void)
{
	char	cwd[1024];

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
		add_history(tmp);
		if (!tmp)
		{
			free_2d(envp);
			free(tmp);
			printf("exit\n");
			exit(0);
		}//have to add some exiting things
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
