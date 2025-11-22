/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:18:14 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/22 12:03:12 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

static void	cleanup_and_exit(t_mother_shell *shell, int status)
{
	if (shell && shell->last_expanded_tokens)
	{
		free_tokens(shell->last_expanded_tokens);
		shell->last_expanded_tokens = NULL;
	}
	if (shell)
		free_shell(shell);
	rl_clear_history();
	close_inherited_fds();
	exit(status);
}

static void	execute_pipe_left(t_node *node, t_mother_shell *shell, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_ast(node->left, shell);
	cleanup_and_exit(shell, shell->last_status);
}

static void	execute_pipe_right(t_node *node, t_mother_shell *shell, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	execute_ast(node->right, shell);
	cleanup_and_exit(shell, shell->last_status);
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
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd(RED, STDERR_FILENO);
			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
			ft_putendl_fd(RESET, STDERR_FILENO);
		}
	}
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

	fd = -1;
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
	(void)shell;
	(void)node;
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (execute_simple_command(node, shell));
	else if (node->type == NODE_PIPE)
		return (execute_pipe(node, shell));
	return (0);
}


