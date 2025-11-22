/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:37:50 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/22 12:01:15 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include "expand_vars.h"

static void	child_exit_with_cleanup(t_node *node, t_mother_shell *shell,
		int status)
{
	(void)node;
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

/* static  */void	execute_builtin_child(t_node *node, t_mother_shell *shell)
{
	ft_exebuiltin(node->command->argv, &shell->env,
	&shell->last_status, STDOUT_FILENO, shell);
	child_exit_with_cleanup(node, shell, shell->last_status);
}

/* static  */void	execute_external_child(t_node *node, t_mother_shell *shell)
{
	char	*cmd_path;
	int		i;
	int		exit_code;

	i = 0;
	while (node->command->argv && node->command->argv[i])
	{
		node->command->argv[i] = clean_final_marker(node->command->argv[i]);
		i++;
	}
	cmd_path = get_path(node->command->argv[0], shell->env);
	if (!cmd_path)
	{
		ft_puterror(node->command->argv[0], NULL, "command not found");
		child_exit_with_cleanup(node, shell, 127);
	}
	exit_code = 0;
	if (!ft_check_path_builtin(cmd_path, &exit_code))
	{
		free(cmd_path);
		child_exit_with_cleanup(node, shell, exit_code);
	}
	execve(cmd_path, node->command->argv, shell->env);
	ft_puterror(cmd_path, NULL, strerror(errno));
	free(cmd_path);
	child_exit_with_cleanup(node, shell, 126);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (handle_redirections(node->command->redir) == -1)
			child_exit_with_cleanup(node, shell, 1);
		if (ft_isbuiltin(node->command->argv[0]))
			execute_builtin_child(node, shell);
		execute_external_child(node, shell);
	}
	waitpid(pid, &status, 0);
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
** Exécute une commande simple (NODE_COMMAND)
*/
int	execute_simple_command(t_node *node, t_mother_shell *shell)
{
	int	*fds;
	int	count;

	if (!node || !node->command)
		return (0);
	if (!node->command->argv || !node->command->argv[0])
	{
		if (node->command->redir)
		{
			if (validate_all_redirections(node->command->redir, &fds, &count) == -1)
			{
				shell->last_status = 1;
				return (0);
			}
			close_validation_fds(fds, count);
		}
		shell->last_status = 0;
		return (0);
	}
	if (node->command->argv[0][0] == '\0')
	{
		ft_putstr_fd(": command not found\n", 2);
		shell->last_status = 127;
		return (0);
	}
	if (ft_strcmp(node->command->argv[0], ".") == 0)
	{
		if (!node->command->argv[1])
		{
			ft_putstr_fd(".: filename argument required\n", 2);
			shell->last_status = 2;
			return (0);
		}
	}
	if (ft_strcmp(node->command->argv[0], "..") == 0)
	{
		ft_putstr_fd("..: command not found\n", 2);
		shell->last_status = 127;
		return (0);
	}
	if (ft_isbuiltin(node->command->argv[0]) && !node->command->redir)
	{
		ft_exebuiltin(node->command->argv, &shell->env,
			&shell->last_status, STDOUT_FILENO, shell);
		return (0);
	}
	return (execute_forked_command(node, shell));
}
