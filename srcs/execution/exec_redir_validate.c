/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:28:24 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/14 17:47:55 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_file(t_redirect *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIR_HEREDOC)
		fd = open(redir->filename, O_RDONLY);
	return (fd);
}

static int	validate_and_store(t_redirect *redir, int *fds, int *count)
{
	t_redirect	*current;
	int			fd;
	int			i;

	(void)count;
	i = 0;
	current = redir;
	while (current)
	{
		fd = open_redir_file(current);
		if (fd == -1)
		{
			perror(current->filename);
			while (--i >= 0)
				if (fds[i] != -1)
					close(fds[i]);
			return (-1);
		}
		fds[i++] = fd;
		current = current->next;
	}
	return (0);
}

int	validate_all_redirections(t_redirect *redir, int **fds_out, int *count_out)
{
	t_redirect	*current;
	int			*fds;
	int			i;

	*count_out = 0;
	current = redir;
	while (current && ++(*count_out))
		current = current->next;
	fds = malloc(sizeof(int) * (*count_out));
	if (!fds)
		return (-1);
	i = 0;
	while (i < *count_out)
		fds[i++] = -1;
	if (validate_and_store(redir, fds, count_out) == -1)
	{
		free(fds);
		return (-1);
	}
	*fds_out = fds;
	return (0);
}
