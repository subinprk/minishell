/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:12:42 by irivero-          #+#    #+#             */
/*   Updated: 2023/12/08 16:11:57 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* checks if a given str is a valid env name*/
/* int is_valid_env_variable_name (char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (ft_isalnum(str[i]) || str[i] == '_')
            ;
        else
            return (0);
    }
    if (i == 0)
        return (0);
    return (1);
}

// checks if a key mathces the beginning of an env var entry 
int	check_env_variable(char *key, char *env)
{
	int i;

	i = 0;
	while (key[i] && env[i] && (key[i] == env[i]) && (env[i] != '='))
		i++;
	if (key[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

// removes an env var by replacing it with the last one in the array
int unset_enviroment_variable(char *key, char ***env)
{
	int last;
	int i;

	last = 0;
	while (((*env)[last] != NULL))
		last++;
	if (last < 1)
		return (0);
	i = -1;
	while ((*env)[++i] != NULL)
	{
		if (check_env_variable(key, (*env)[i]))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup((*env)[last - 1]);
			free((*env)[last - 1]);
			(*env)[last - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

// executes the unset command, removing specified enviroment variables
void    execute_unset_command(t_cmd *cmd, char **cmdline)
{
    int i;
    int result;

	if (cmd == NULL)
		return ;
    i = 0;
    result = 0;
    while (cmdline[++i])
    {
        remove_char(cmdline[i], '\'');
        result = is_valid_env_variable_name(cmdline[i]) && unset_enviroment_variable(cmdline[i], &g_envp);
    }
    if (result != 1)
        g_exit_status = 1;        
} */

/* int	f_strcmpt(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i ++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

int	last_variable(char **env)
{
	int	i = 0;
	while (env[i + 1] != NULL)
		i++;
	return (i);
}

void	ft_unset(char **cmdline, t_envp *env)
{
	int	i = 0, lv;
	char	*v_name;

	v_name = cmdline[1];
	while (env->envp[i] != NULL)	// if the variable does not exist in env, and it goes to NULL?
	{
	//printf("vname: <%s>\n", v_name);
		if (f_strcmpt(v_name, env->envp[i]) == 0)
		{
			if (env->envp[i + 1] == NULL)
			{
				env->envp[i] = NULL;
				return ;
			}
			else
			{
				lv = last_variable(env->envp);
				env->envp[i] = env->envp[lv];
				env->envp[lv] = NULL;
				return ;
			}
		}
		i++;
	}
	return ;
} */

int     f_strcmpt(char *s1, char *s2)
{
        int     i;

        i = 0;
        while (s1[i] && s2[i])
        {
                if (s1[i] == s2[i])
                        i ++;
                else
                        return (s1[i] - s2[i]);
        }
        return (0);
}

int     last_variable(char **env)
{
        int     i;

        i = 0;
        while (env[i + 1] != NULL)
                i++;
        return (i);
}

void    ft_unset(char *v_name, t_envp *env)
{
        int     i;
        int     lv;

        i = 0;
        while (env->envp[i] != NULL)
        {
                if (f_strcmpt(v_name, env->envp[i]) == 0)
                {
                        if (env->envp[i + 1] == NULL)
                        {
                                env->envp[i] = NULL;
                                return ;
                        }
                        else
                        {
                                lv = last_variable(env->envp);
                                env->envp[i] = env->envp[lv];
                                env->envp[lv] = NULL;
                                return ;
                        }
                }
                i++;
        }
        return ;
}