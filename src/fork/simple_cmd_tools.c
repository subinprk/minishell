/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:11:50 by subpark           #+#    #+#             */
/*   Updated: 2023/12/12 21:21:00 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_cmd(t_cmd *file_path, char **envp)
{
	char	*path_buf;

	path_buf = path_pointer(envp, file_path->cmdstr[0]);
	if (!path_buf)
	{
		printf("%s: ", file_path->cmdstr[0]);
		if (errno != 2)
			perror("");
		else
			printf("command not found\n");
	}
	free(path_buf);
	return ;
}

int	check_builtin(t_cmd *file_path)
{
	if (!ft_strcmp(file_path->cmdstr[0], "echo") || !ft_strcmp(file_path->cmdstr[0], "cd")
		|| !ft_strcmp(file_path->cmdstr[0], "pwd") || !ft_strcmp(file_path->cmdstr[0], "export")
		|| !ft_strcmp(file_path->cmdstr[0], "unset") || !ft_strcmp(file_path->cmdstr[0], "env")
		|| !ft_strcmp(file_path->cmdstr[0], "exit"))
		return (1);
	else
		return (0);
}

void	builtin_action(t_cmd *builtin, char **cmdline, t_envp *env)
{
	if (!ft_strcmp(builtin->cmdstr[0], "echo"))
		our_echo(cmdline);
	//else if (!ft_strcmp(builtin->cmdstr[0], "cd"))
	//	change_directory(cmdline, g_envp);
	else if (!ft_strcmp(builtin->cmdstr[0], "pwd"))
		our_pwd(builtin->cmdstr);
	//else if (!ft_strcmp(builtin->cmdstr[0], "export"))
	//	export(builtin->cmdstr + 1, env);
	//else if (!ft_strcmp(builtin->cmdstr[0], "unset"))
	//	ft_unset(cmdline, env);
	else if (!ft_strcmp(builtin->cmdstr[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(builtin->cmdstr[0], "exit"))
		exit_command();
}