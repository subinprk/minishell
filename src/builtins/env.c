/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:43:36 by irivero-          #+#    #+#             */
/*   Updated: 2023/12/05 15:00:12 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*takes an array of strings representing comand-line args.
It iterates through the array and prints each element on a new line*/
void	ft_env(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	g_exit_status = 0;
}