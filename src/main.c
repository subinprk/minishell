/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:48:01 by subpark           #+#    #+#             */
/*   Updated: 2024/02/08 17:36:02 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_exit_status = 0;

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
			exit(0);
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
}
