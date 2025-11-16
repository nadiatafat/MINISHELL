/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:18:14 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/16 20:54:54 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_pipe_left(t_node *node, t_mother_shell *shell, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_ast(node->left, shell);
	exit(shell->last_status);
}

static void	execute_pipe_right(t_node *node, t_mother_shell *shell, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	execute_ast(node->right, shell);
	exit(shell->last_status);
}

/*
** Exécute un pipe (NODE_PIPE)
*/
int	execute_pipe(t_node *node, t_mother_shell *shell)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid1 = fork();
	if (pid1 == 0)
		execute_pipe_left(node, shell, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		execute_pipe_right(node, shell, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	return (0);
}

/*
** CORRECTION: Vérifie les redirections AVANT d'exécuter
** Retourne 0 si OK, 1 si erreur
*/
int	check_redirections_validity(t_redirect *redir)
{
	t_redirect	*current;
	int			fd;

	current = redir;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
			fd = open(current->filename, O_RDONLY);
		else if (current->type == REDIR_OUT)
			fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == REDIR_APPEND)
			fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(current->filename);
			return (1);
		}
		close(fd);
		current = current->next;
	}
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

