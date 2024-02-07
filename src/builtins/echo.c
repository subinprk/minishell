/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:02:32 by irivero-          #+#    #+#             */
/*   Updated: 2023/12/05 09:28:09 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*prints the global exit status to the standard output*/
/* void	exit_status(void)
{
	ft_putstr_fd(ft_itoa(g_exit_status), 1);
}

// handles echoing env variables based on cmdline arg
void	echo_env_variable(char **cmdline, char **envs, int i)
{
	char	*value;

	//if the cmdline arg is $?, print the exit status
	if (cmdline[1][1] == '?' && cmdline[1][0] == '$')
		exit_status();
	//find the value of the env variable and print it
	else
	{
		value = get_env_value(&(cmdline[i][1]), envs);
		if (value != NULL)
			ft_putstr_fd(value, 1);
	}
}

// checks if a cmdline arg is the "-n" option
int	is_option_n(char *token)
{
	int i;

	//compare the cmdline arg to "-n"
	if (ft_strncmp(token, "-n", 2) == 0)
		return (0);
	i = 2;
	while (token[i])
	{
		//check if the rest of the arg is 'n'
		if (token[i] != 'n')
			return (0);
		i++;
	}
	//the arg is the "-n" option
	return (1);
}

// simulates the behavior of the echo command
void	our_echo(char **cmdline, char **envs)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	//handle the "-n" option
	while (is_option_n(cmdline[i]))
	{
		ret = -1;
		i++;
	}
	//iterate through the cmdline args and print them
	while (cmdline[i])
	{
		//echo env variables or print the cmdline arg
		if (cmdline[i][0] == '$' && ret != -1)
			echo_env_variable(cmdline, envs, i);
		else
			ft_putstr_fd(cmdline[i], 1);
		//remove the quotes from the arg
		if (cmdline[i][0] == '\'')
			ret = remove_char(cmdline[i], '\'');
		//print a space between args if not the last arg
		if (cmdline[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	//print a new line if the "-n" option was not used
	if (ret != -1)
		ft_putchar_fd('\n', 1);
} */

/* int	f_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	f_putstr(char *s)
{
	write(1, s, ft_strlen(s));
	return (0);
}

int	f_strchr(char *s, char c)
{
	int	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

void	our_echo(char **av)
{
	int	i;
	char	c;

	c = 'y';
	i = 1;
	if (f_strcmp("-n", av[1]) == 0)
	{
		i = 2;
		c = 'n';
	}
	while (av[i] != NULL)
	{
		f_putstr(av[i]);
		if (av[i + 1] != NULL)
			write(1, " ", 1);
		if (av[i + 1] == NULL && c == 'y')
			write(1, "\n", 1);
		i++;
	}
	return ;
} */

int     f_strcmp(char *s1, char *s2)
{
        unsigned int    i;

        i = 0;
        while (s1[i] != '\0' && s2[i] != '\0')
        {
                if (s1[i] != s2[i])
                        return (-1);
                i++;
        }
        return (0);
}

int     f_putstr(char *s)
{
        write(1, s, ft_strlen(s));
        return (0);
}

int     f_strchr(char *s, char c)
{
        int     i;

        i = 0;
        while (s[i] != c && s[i] != '\0')
                i++;
        if (s[i] == '\0')
                return (-1);
        return (i);
}

int     echo_helper(char **av, char *c, int *i)
{
        if (av[1] == NULL)
        {
                write(1, "\n", 1);
                return (1);
        }
        if (f_strcmp("-n", av[1]) == 0)
        {
                *i = 2;
                *c = 'n';
        }
        if (ft_strcmp("$?", av[1]) != 0 && f_strcmp("$?", av[1]) == 0)
        {
                printf("no matches found: 0?\n");
                g_exit_status = 1;
                return (1);
        }
        else if (ft_strcmp("$?", av[1]) == 0)
        {
                printf("%i\n", g_exit_status);
                return (1);
        }
        return (0);
}

void    our_echo(char **av)
{
        int             i;
        char    c;

        c = 'y';
        i = 1;
        if (echo_helper(av, &c, &i) == 1)
                return ;
        while (av[i] != NULL)
        {
                f_putstr(av[i]);
                if (av[i + 1] != NULL)
                        write(1, " ", 1);
                if (av[i + 1] == NULL && c == 'y' && av[i][0] != '\n')
                        write(1, "\n", 1);
                i++;
        }
        g_exit_status = 0;
        return ;
}