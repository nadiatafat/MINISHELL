/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:18:14 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/12 21:20:41 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Exécute une commande simple (NODE_COMMAND)
*/
static int	execute_simple_command(t_node *node, t_mother_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (!node || !node->command || !node->command->argv[0])
		return (0);

	// Si builtin SANS redirections, exécuter directement
	if (ft_isbuiltin(node->command->argv[0]) && !node->command->redir)
	{
		ft_exebuiltin(node->command->argv, &shell->env,
			&shell->last_status, STDOUT_FILENO);
		return (0);
	}

	// Sinon, fork (builtin avec redir OU commande externe)
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		// Processus enfant
		handle_redirections(node->command->redir);

		if (ft_isbuiltin(node->command->argv[0]))
		{
			ft_exebuiltin(node->command->argv, &shell->env,
				&shell->last_status, STDOUT_FILENO);
			exit(shell->last_status);
		}

		cmd_path = get_path(node->command->argv[0], shell->env);
		if (!cmd_path)
			ft_exit_error(node->command->argv[0],
				"command not found", 127, node->command);
		ft_check_path(cmd_path, node->command);
		execve(cmd_path, node->command->argv, shell->env);
		ft_exit_error(cmd_path, strerror(errno), 126, node->command);
	}
	// Processus parent
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	return (0);
}

/*
** Exécute un pipe (NODE_PIPE)
*/
static int	execute_pipe(t_node *node, t_mother_shell *shell)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid1 = fork();
	if (pid1 == 0)
	{
		// Commande gauche
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (node->left->type == NODE_COMMAND)
		{
			handle_redirections(node->left->command->redir);
			if (ft_isbuiltin(node->left->command->argv[0]))
				ft_exebuiltin(node->left->command->argv, &shell->env,
					&shell->last_status, STDOUT_FILENO);
			else
			{
				char *path = get_path(node->left->command->argv[0], shell->env);
				if (!path)
					ft_exit_error(node->left->command->argv[0],
						"command not found", 127, node->left->command);
				ft_check_path(path, node->left->command);
				execve(path, node->left->command->argv, shell->env);
				ft_exit_error(path, strerror(errno), 126, node->left->command);
			}
		}
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		// Commande droite
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		if (node->right->type == NODE_COMMAND)
		{
			handle_redirections(node->right->command->redir);
			if (ft_isbuiltin(node->right->command->argv[0]))
				ft_exebuiltin(node->right->command->argv, &shell->env,
					&shell->last_status, STDOUT_FILENO);
			else
			{
				char *path = get_path(node->right->command->argv[0], shell->env);
				if (!path)
					ft_exit_error(node->right->command->argv[0],
						"command not found", 127, node->right->command);
				ft_check_path(path, node->right->command);
				execve(path, node->right->command->argv, shell->env);
				ft_exit_error(path, strerror(errno), 126, node->right->command);
			}
		}
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	return (0);
}

/*
** Fonction principale d'exécution de l'AST
*/
int	execute_ast(t_node *node, t_mother_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (execute_simple_command(node, shell));
	else if (node->type == NODE_PIPE)
		return (execute_pipe(node, shell));
	return (0);
}
