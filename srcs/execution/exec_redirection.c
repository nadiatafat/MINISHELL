// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec_redirection.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/18 12:28:24 by nadgalle          #+#    #+#             */
// /*   Updated: 2025/11/07 16:13:40 by nadgalle         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

/*
check_permission : vérifie les permissions d'accès à un fichier
write_flag = 0 : check lecture (R_OK)
write_flag = 1 : check écriture (W_OK)
*/
static void check_permission(t_command *command, int write_flag)
{
	t_redirect *redir;

	if (!command || !command->redir)
		return;
	redir = command->redir;

	if (write_flag == 0) // lecture
	{
		if (access(redir->filename, F_OK) != 0 || access(redir->filename, R_OK) != 0)
		{
			if (access(redir->filename, F_OK) == 0)
				ft_exit_free("Permission denied", EXIT_FAILURE, command);
			ft_exit_free(redir->filename, EXIT_FAILURE, command);
		}
	}
	else // écriture
	{
		if (access(redir->filename, F_OK) == 0 && access(redir->filename, W_OK) != 0)
			ft_exit_free("Permission denied", EXIT_FAILURE, command);
	}
}

/*
Redirection d'entrée normale : <
Parcourt toutes les REDIR_IN, garde la dernière pour stdin
*/
void	infile_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_IN && cur->filename)
		{
			if (fd != -1)
				close(fd);
			check_permission(command, 0); // 0 = lecture
			fd = open(cur->filename, O_RDONLY);
			if (fd == -1)
				ft_exit_free(cur->filename, EXIT_FAILURE, command);
		}
		cur = cur->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_exit_free("dup2 input", EXIT_FAILURE, command);
		close(fd);
	}
}

/*
Redirection heredoc : <<
Appelle get_heredoc() pour obtenir le fd final de stdin
*/
void	heredoc_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_HEREDOC)
		{
			if (fd != -1)
				close(fd);
			fd = get_heredoc(command);
			if (fd == -1)
				ft_exit_free("heredoc", EXIT_FAILURE, command);
		}
		cur = cur->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_exit_free("dup2 heredoc", EXIT_FAILURE, command);
		close(fd);
	}
}

/*
Redirection de sortie : > (truncate)
Parcourt toutes les REDIR_OUT, garde la dernière pour stdout
*/
void	outfile_truncate_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_OUT && cur->filename)
		{
			if (fd != -1)
				close(fd);
			check_permission(command, 1); // 1 = écriture
			fd = open(cur->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				ft_exit_free(cur->filename, EXIT_FAILURE, command);
		}
		cur = cur->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_exit_free("dup2 output", EXIT_FAILURE, command);
		close(fd);
	}
}

/*
Redirection de sortie : >> (append)
 Parcourt toutes les REDIR_APPEND, garde la dernière pour stdout
*/
void	outfile_append_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_APPEND && cur->filename)
		{
			if (fd != -1)
				close(fd);
			check_permission(command, 1); // 1 = écriture
			fd = open(cur->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				ft_exit_free(cur->filename, EXIT_FAILURE, command);
		}
		cur = cur->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_exit_free("dup2 append", EXIT_FAILURE, command);
		close(fd);
	}
}

/*
** Applique une redirection d'entrée (<)
** Ouvre le fichier et redirige stdin
*/
static int	apply_redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
** Applique une redirection de sortie (>)
** Ouvre/crée le fichier en mode troncate et redirige stdout
*/
static int	apply_redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
** Applique une redirection de sortie en mode append (>>)
** Ouvre/crée le fichier en mode append et redirige stdout
*/
static int	apply_redir_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
** Gère le heredoc (<<)
** Note: Le heredoc devrait être traité avant l'exécution
** Cette fonction suppose que le contenu est dans un fichier temporaire
*/
static int	apply_redir_heredoc(char *delimiter)
{
	char	*line;
	int		pipefd[2];

	(void)delimiter;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	/* Ici, vous devriez lire les lignes jusqu'au délimiteur */
	/* Pour l'instant, version simplifiée */
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}


/*
** Parcourt et applique toutes les redirections d'une commande
** Retourne 0 en cas de succès, -1 en cas d'erreur
*/
int	handle_redirections(t_redirect *redir)
{
	t_redirect	*current;

	current = redir;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			if (apply_redir_in(current->filename) == -1)
				return (-1);
		}
		else if (current->type == REDIR_OUT)
		{
			if (apply_redir_out(current->filename) == -1)
				return (-1);
		}
		else if (current->type == REDIR_APPEND)
		{
			if (apply_redir_append(current->filename) == -1)
				return (-1);
		}
		else if (current->type == REDIR_HEREDOC)
		{
			if (apply_redir_heredoc(current->filename) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}





/*
** Redirections dans le processus enfant
** Gère toutes les redirections (infile, outfile, append, heredoc)
** puis ferme les descripteurs de pipe inutiles.
*
void	handle_child_redirection(t_command *command)
{
	if (!command)
		return;
	heredoc_redirection(command);
	infile_redirection(command);
	outfile_truncate_redirection(command);
	outfile_append_redirection(command);
	if (command->pipe_fd[0] != -1)
		close(command->pipe_fd[0]);
	if (command->pipe_fd[1] != -1)
		close(command->pipe_fd[1]);
}*/

/*
** Redirections dans le processus parent
** Ferme les descripteurs inutiles après le fork et prépare le stdin du prochain
** maillon de la pipeline si nécessaire.
*
void	handle_parent_redirection(t_command *command)
{
	if (!command)
		return;
	if (command->pipe_fd[1] != -1)
		close(command->pipe_fd[1]);
	if (command->input_fd != -1 && command->input_fd != STDIN_FILENO)
		close(command->input_fd);
	if (command->output_fd != -1 && command->output_fd != STDOUT_FILENO)
		close(command->output_fd);
	if (command->heredoc_fd != -1 && command->heredoc_fd != STDIN_FILENO)
		close(command->heredoc_fd);
	if (command->next)
	{
		if (command->pipe_fd[0] != -1)
		{
			if (dup2(command->pipe_fd[0], STDIN_FILENO) == -1)
				ft_exit_free("pipe", EXIT_FAILURE, command, NULL);
			close(command->pipe_fd[0]);
		}
	}
	else if (command->pipe_fd[0] != -1)
		close(command->pipe_fd[0]);
}
*/
