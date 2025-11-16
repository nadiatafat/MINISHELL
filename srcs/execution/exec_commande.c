/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:37:50 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/16 17:55:35 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_builtin_child(t_node *node, t_mother_shell *shell)
{
	ft_exebuiltin(node->command->argv, &shell->env,
		&shell->last_status, STDOUT_FILENO);
	exit(shell->last_status);
}

static void	execute_external_child(t_node *node, t_mother_shell *shell)
{
	char	*cmd_path;

	cmd_path = get_path(node->command->argv[0], shell->env);
	if (!cmd_path)
		ft_exit_error(node->command->argv[0],
			"command not found", 127, node->command);
	ft_check_path(cmd_path, node->command);
	execve(cmd_path, node->command->argv, shell->env);
	ft_exit_error(cmd_path, strerror(errno), 126, node->command);
}

static int	execute_forked_command(t_node *node, t_mother_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (handle_redirections(node->command->redir) == -1)
			exit(1);
		if (ft_isbuiltin(node->command->argv[0]))
			execute_builtin_child(node, shell);
		execute_external_child(node, shell);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	return (0);
}

/*
** Exécute une commande simple (NODE_COMMAND)
*/
int	execute_simple_command(t_node *node, t_mother_shell *shell)
{
	if (!node || !node->command || !node->command->argv[0])
		return (0);
	if (ft_isbuiltin(node->command->argv[0]) && !node->command->redir)
	{
		ft_exebuiltin(node->command->argv, &shell->env,
			&shell->last_status, STDOUT_FILENO);
		return (0);
	}
	return (execute_forked_command(node, shell));
}
