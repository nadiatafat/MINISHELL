/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:22 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/22 14:32:13 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"


static int	validate_exit_args(char **tokens, int *exit_status)
{
	if (!tokens[1])
		return (1);
	if (ft_strcmp(tokens[0], "env") == 0)
	{
		*exit_status = 127;
		return (0);
	}
	if (!ft_isnumber(tokens[1]))
	{
		ft_putstr_fd("exit\n", 1);
		ft_puterror("exit", NULL, "numeric argument required");
		*exit_status = 2;
		return (0);
	}
	*exit_status = ft_atoi(tokens[1]);
	if (tab_size(tokens) > 2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_puterror("exit", NULL, "too many arguments");
		*exit_status = 1;
		return (0);
	}
	return (1);
}

void	ft_exit(char **tokens, int *exit_status, t_mother_shell *shell)
{
	if (!validate_exit_args(tokens, exit_status))
		return ;
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	close_inherited_fds();
	if (shell)
		free_shell(shell);
	exit(*exit_status);
}

/*void	ft_exit(char **tokens, int *exit_status, t_mother_shell *shell)
{

	if (tokens[1])
	{
		if (ft_strcmp(tokens[0], "env") == 0)
		{
			*exit_status = 127;
			return ;
		}
		else
		{
			if (ft_isnumber(tokens[1]))
				*exit_status = ft_atoi(tokens[1]);
			else
			{
				ft_putstr_fd("exit\n", 1);
				ft_puterror("exit", NULL, "numeric argument required");
				*exit_status = 2;
				return ;
			}
			if (tab_size(tokens) > 2)
			{
				ft_putstr_fd("exit\n", 1);
				ft_puterror("exit", NULL, "too many arguments");
				*exit_status = 1;
				return ;
			}
		}
	}
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	close_inherited_fds();
	//rl_clear_history();
	if (shell)
		free_shell(shell);
	exit(*exit_status);
}*/

