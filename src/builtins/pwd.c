/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:35:29 by irivero-          #+#    #+#             */
/*   Updated: 2023/12/05 09:30:31 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*retrieves and prints the current working directory. It uses the getcwd
function to obtain the path, then prints tp the standard output.
Then frees the memory in getcwd. */
/* void   	our_pwd(void)
{
	char	*current_directory;
	//int		status;

	//status = EXIT_SUCCESS;
	current_directory = getcwd(0, 1024);
	ft_putendl_fd(current_directory, 1);
	free(current_directory);
	g_exit_status = 0;
} */

void	our_pwd(char **av)
{
	char	path[1024];
	int	i = 0;

	while (av[i])
		i++;
	if (i > 1)
	{
		printf("Look up how to use 'pwd' please!!\n");
		return ;
	}
	if (getcwd(path, sizeof(path)) == NULL)
	{
		g_exit_status = 127;
		return ;
	}
	write(1, path, f_strlen(path));
	write(1, "\n", 1);
	g_exit_status = 0;
	return ;
}