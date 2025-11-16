/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:28:24 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/16 17:57:33 by sdossa           ###   ########.fr       */
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

static void	apply_redir(t_redirect *redir)
{
	int	fd;

	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
	{
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
}

/*
** Parcourt et applique toutes les redirections
** !! = Cette ft ne doit être appelée QUE si validate_all_redirections
** a réussi. Elle réouvre les fichiers et applique les redirections.
*/
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
}
