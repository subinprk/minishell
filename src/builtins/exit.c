/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:59:47 by irivero-          #+#    #+#             */
/*   Updated: 2023/12/08 16:32:26 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* void    exit_err(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_status);
}

void    exit_command(t_cmd *cmd, char **cmdline)
{
	int ac;

	if (cmd == NULL)
		return ;
	ac = 0;
	while (cmdline[ac] != NULL) //counts the number of arguments
		ac++;
	if (ac == 1)
		exit_err(); //if ac is 1 just exit
	if (ac == 2 && is_stringdigit(cmdline[1])) // if ac is 2 and the second argument is a number, it stores in g_exit status
		g_exit_status = ft_atoi(cmdline[1]);
	if (ac > 2 && is_stringdigit(cmdline[1])) // deals if there are too many ac
	{
		ft_putstr_fd("exit\n", 1);
		print_error("exit", "too many arguments");
		g_exit_status = 1;
	}
	else // deals if the second argument is not a number
	{
		print_error2("exit", cmdline[1], "numeric argument required");
		// if it reaches this part it means that an error happened, and the exit status is set to 255
		// the code 255 its truncated to 8 bits using & 255
		g_exit_status = 255;
		exit(g_exit_status & 255);
	}
	exit_err();
} */

/* void	exit_command(void)
{
	exit(g_exit_status);
} */

int     av_counter(char **av)
{
        int     i;

        i = 0;
        while (av[i])
                i++;
        return (i);
}

void    if_i_is_two(char **av)
{
        if (ft_isdigit(av[1][0]) == 0)
        {
                printf("exit: %s: numeric argument required\n", av[1]);
                g_exit_status = 2;
        }
        else
        {
                g_exit_status = ft_atoi(av[1]);
                exit(g_exit_status);
        }
}

void    exit_command(char **av)
{
        int             i;

        i = av_counter(av);
        if (i > 2)
        {
                printf("exit: too many arguments\n");
                g_exit_status = 1;
        }
        else if (i == 1)
        {
                g_exit_status = 0;
                exit(g_exit_status);
        }
        else if (i == 2)
                if_i_is_two(av);
        exit (g_exit_status);
}