/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:54:53 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/21 16:03:30 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tabchr_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_cd(char **tokens, int *exit_status, char **env)
{
	char	*path_to_go;
	char	cwd[PATH_MAX];

	path_to_go = tokens[1];
	if (!path_to_go)
	{
		if (ft_tabchr_home(env))
			path_to_go = getenv("HOME");
		if (!path_to_go || path_to_go[0] == '\0')
		{
			ft_error_builtin("cd", "HOME not set", 1, exit_status);
			return ;
		}
	}
	if (tab_size(tokens) > 2)
	{
		ft_error_builtin("cd", "too many arguments", 1, exit_status);
		return ;
	}
	if (chdir(path_to_go) < 0 || !getcwd(cwd, sizeof(cwd)))
	{
		ft_puterror("cd", path_to_go, strerror(errno));
		*exit_status = 1;
	}
}

void	ft_cd_invalid_opt(char **tokens, int *exit_code, char **env)
{
	if (tokens[1] && tokens[1][0] == '-' && tokens[1][1] != '\0')
	{
		if (ft_strcmp(tokens[1], "-") == 0)
		{
			ft_error_builtin("cd", "OLDPWD not set", 1, exit_code);
			return ;
		}
		ft_puterror("cd", tokens[1], "invalid option");
		*exit_code = 2;
		return ;
	}
	ft_cd(tokens, exit_code, env);
}
