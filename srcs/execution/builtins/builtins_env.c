/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:55:19 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/12 17:21:06 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup2(char *src, int n)
{
	char	*dup;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, n + 1);
	return (dup);
}

void	ft_env(char **envp, int output_fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (output_fd)
		{
			ft_putstr_fd(envp[i], output_fd);
			ft_putstr_fd("\n", output_fd);
		}
		else
			printf("%s\n", envp[i]);
		i++;
	}
}

char	**ft_minimal_env(char **envp)
{
	char	*pwd;
	char	*shlvl;
	char	*underscore;
	char	*path;
	char	cwd[PATH_MAX];

	pwd = getenv("PWD");
	if (!pwd)
	{
		pwd = "PWD=";
		path = ft_strdup(getcwd(cwd, sizeof(cwd)));
		pwd = ft_strjoin(pwd, path);
		free(path);
	}
	shlvl = getenv("SHLVL");
	if (!shlvl)
		shlvl = "SHLVL=1";
	underscore = getenv("_");
	if (!underscore)
		underscore = "_=/usr/bin/env";
	envp = NULL;
	envp = ft_add_to_array(envp, pwd);
	envp = ft_add_to_array(envp, shlvl);
	envp = ft_add_to_array(envp, underscore);
	return (envp);
}
