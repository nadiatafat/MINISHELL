/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:33:45 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/12 14:21:23 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Affiche un message d’erreur formaté et quitte proprement le programme.
** Exemple : ft_exit_error(path, "Permission denied", 126, command);
*/
void	ft_exit_error(char *path, char *error, int code, t_command *cmd)
{
	ft_puterror(path, NULL, error);
	ft_exit_free(NULL, code, cmd, NULL);
}

#include "../../includes/minishell.h"

/*
** Libère les fichiers et arguments associés à une commande.
*/
static void	free_command_files_and_args(t_command *command)
{
	if (!command)
		return;
	if (command->input_file)
		free(command->input_file);
	if (command->output_file)
		free(command->output_file);
	if (command->limiter)
		free(command->limiter);
	if (command->argv)
		ft_free_tab(command->argv);
	if (command->command_args)
		ft_free_tab(command->command_args);
}

/*
** Libère toutes les redirections (liste chaînée de t_redirect).
*/
static void	free_command_redirections(t_command *command)
{
	t_redirect	*redir;
	t_redirect	*tmp;

	if (!command || !command->redir)
		return;
	redir = command->redir;
	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

/*
** Ferme les descripteurs de fichiers ouverts (> 2 pour éviter stdin/out/err).
*/
static void	close_command_fds(t_command *command)
{
	if (!command)
		return;
	if (command->input_fd > 2)
		close(command->input_fd);
	if (command->output_fd > 2)
		close(command->output_fd);
	if (command->heredoc_fd > 2)
		close(command->heredoc_fd);
	if (command->pipe_fd[0] > 2)
		close(command->pipe_fd[0]);
	if (command->pipe_fd[1] > 2)
		close(command->pipe_fd[1]);
}

/*
** Libère complètement une commande unique :
** - fichiers et arguments
** - redirections
** - descripteurs de fichiers
*/
void	ft_free_command(t_command *command)
{
	if (!command)
		return;
	free_command_files_and_args(command);
	free_command_redirections(command);
	close_command_fds(command);
	free(command);
}


/*
** Quitte le programme en libérant toutes les commandes allouées.
** Si head == NULL, on ne libère que la commande courante.
*/
void	ft_exit_free(char *msg, int status, t_command *cmd, t_command **head)
{
	t_command	*current;
	t_command	*next;

	if (msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(msg);
	}

	if (!head)
		ft_free_command(cmd);
	else
	{
		current = *head;
		while (current)
		{
			next = current->next;
			ft_free_command(current);
			current = next;
		}
		free(head);
	}

	close_inherited_fds();
	exit(status);
}

/*
** Ferme tous les descripteurs hérités (à partir de 3),
** pour éviter les fuites après un fork/exec.
*/
void	close_inherited_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
		close(fd++);
}

/*
** Ignore SIGPIPE pour éviter l’arrêt du shell lors d’un pipe brisé.
*/
void	setup_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGPIPE, &sa, NULL);
}
