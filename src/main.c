/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:48:01 by subpark           #+#    #+#             */
/*   Updated: 2024/02/09 00:38:19 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_exit_status = 0;

char    *print_prompt(void)
{
        char    *cwd;
        int     i;
        cwd = malloc(1024 * sizeof(char));
        getcwd(cwd, 1024);
        i = f_strlen(cwd);
        cwd[i] = ' ';
        cwd[i + 1] = '\0';
        return (cwd);
}

void	interactive_mode(t_cmd **tree, char **envp, t_envp *env)
{
	char	*tmp;
	char	*cwd;
	env->cd_hist = NULL;

	while (1)
	{
		set_signals_interactive(-1);
		cwd = print_prompt();
		tmp = readline(cwd);
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
