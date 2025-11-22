/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:28:24 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/22 11:22:50 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Ferme tous les file descriptors de validation
*/
void	close_validation_fds(int *fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (fds[i] != -1)
			close(fds[i]);
		i++;
	}
	free(fds);
}

static int	validate_redir_phase(t_redirect *tmp)
{
	int	fd;

	fd = -1;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_HEREDOC)
			fd = open(tmp->filename, O_RDONLY);
		else if (tmp->type == REDIR_OUT)
			fd = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == REDIR_APPEND)
			fd = open(tmp->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(tmp->filename);
			return (-1);
		}
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}

// cela fonction mais n'affiche pas les infos du 1er heredoc 21/11/25
static void	apply_redir(t_redirect *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
	{
		fd = open(redir->filename, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_HEREDOC)
	{
		fd = open(redir->filename, O_RDONLY);
		if (fd != -1)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else if (redir->type == REDIR_OUT)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_APPEND)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

/*static void	apply_redir(t_redirect *redir)
{
	int	fd;

	if (redir->type == REDIR_IN )
	{
		fd = open(redir->filename, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_HEREDOC)
	{
		// close(redir->heredoc_fd);
		fd = open(redir->filename, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_OUT)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_APPEND)
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}*/

/*
** Parcourt et applique toutes les redirections
** !! = Cette ft ne doit être appelée QUE si validate_all_redirections
** a réussi. Elle réouvre les fichiers et applique les redirections.
*
// cela fonction mais n'affiche pas les infos du 1er heredoc 21/11/25
int	handle_redirections(t_redirect *redir)
{
	t_redirect	*tmp;
	t_redirect	*cleanup;

	tmp = redir;
	if (validate_redir_phase(tmp) == -1)
		return (-1);
	while (redir)
	{
		apply_redir(redir);
		redir = redir->next;
	}
	// Cleanup heredoc files after use
	cleanup = tmp;
	while (cleanup)
	{
		if (cleanup->type == REDIR_HEREDOC && cleanup->filename)
			unlink(cleanup->filename);
		cleanup = cleanup->next;
	}
	return (0);
}*/

/*
** Parcourt et applique toutes les redirections
** !! = Cette ft ne doit être appelée QUE si validate_all_redirections
** a réussi. Elle réouvre les fichiers et applique les redirections.
*/
int	handle_redirections(t_redirect *redir)
{
	t_redirect	*tmp;
	t_redirect	*cleanup;

	tmp = redir;
	if (validate_redir_phase(tmp) == -1)
		return (-1);
	while (redir)
	{
		apply_redir(redir);
		redir = redir->next;
	}
	cleanup = tmp;
	while (cleanup)
	{
		if (cleanup->type == REDIR_HEREDOC && cleanup->filename)
			unlink(cleanup->filename);
		cleanup = cleanup->next;
	}
	return (0);
}


/*
** Parcourt et applique toutes les redirections
** !! = Cette ft ne doit être appelée QUE si validate_all_redirections
** a réussi. Elle réouvre les fichiers et applique les redirections.
*
int	handle_redirections(t_redirect *redir)
{
	t_redirect	*tmp;
	t_redirect	*cleanup;
	t_redirect	*last_heredoc;

	tmp = redir;
	if (validate_redir_phase(tmp) == -1)
		return (-1);
	// Find last heredoc first
	last_heredoc = NULL;
	cleanup = redir;
	while (cleanup)
	{
		if (cleanup->type == REDIR_HEREDOC)
			last_heredoc = cleanup;
		cleanup = cleanup->next;
	}
	// Apply redirections, skipping non-last heredocs
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC && redir != last_heredoc)
		{
			// Skip non-last heredocs
			redir = redir->next;
			continue;
		}
		apply_redir(redir);
		redir = redir->next;
	}
	// Cleanup heredoc files after use
	cleanup = tmp;
	while (cleanup)
	{
		if (cleanup->type == REDIR_HEREDOC && cleanup->filename)
			unlink(cleanup->filename);
		cleanup = cleanup->next;
	}
	return (0);
}*/

/*
** Parcourt et applique toutes les redirections
** !! = Cette ft ne doit être appelée QUE si validate_all_redirections
** a réussi. Elle réouvre les fichiers et applique les redirections.
*
int	handle_redirections(t_redirect *redir)
{
	t_redirect	*tmp;

	tmp = redir;
	if (validate_redir_phase(tmp) == -1)
		return (-1);
	while (redir)
	{
		apply_redir(redir);
		redir = redir->next;
	}
	return (0);
}*/
