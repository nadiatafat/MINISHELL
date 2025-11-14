/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_inout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:28:24 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/14 17:48:32 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_and_open_file(t_command *cmd, t_redirect *cur, int flags,
			int *fd)
{
	t_redirect	*redir;

	redir = cmd->redir;
	if (flags == O_RDONLY)
	{
		if (access(redir->filename, F_OK) != 0
			|| access(redir->filename, R_OK) != 0)
		{
			if (access(redir->filename, F_OK) == 0)
				ft_exit_free("Permission denied", EXIT_FAILURE, cmd);
			ft_exit_free(redir->filename, EXIT_FAILURE, cmd);
		}
	}
	else if (access(redir->filename, F_OK) == 0
		&& access(redir->filename, W_OK) != 0)
		ft_exit_free("Permission denied", EXIT_FAILURE, cmd);
	if (*fd != -1)
		close(*fd);
	*fd = open(cur->filename, flags, 0644);
	if (*fd == -1)
		ft_exit_free(cur->filename, EXIT_FAILURE, cmd);
}

static void	apply_fd_to_stdio(int fd, int stdio_fd, char *err, t_command *cmd)
{
	if (fd != -1)
	{
		if (dup2(fd, stdio_fd) == -1)
			ft_exit_free(err, EXIT_FAILURE, cmd);
		close(fd);
	}
}

void	infile_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_IN && cur->filename)
			check_and_open_file(command, cur, O_RDONLY, &fd);
		cur = cur->next;
	}
	apply_fd_to_stdio(fd, STDIN_FILENO, "dup2 input", command);
}


void	outfile_truncate_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_OUT && cur->filename)
			check_and_open_file(command, cur,
				O_WRONLY | O_CREAT | O_TRUNC, &fd);
		cur = cur->next;
	}
	apply_fd_to_stdio(fd, STDOUT_FILENO, "dup2 output", command);
}

void	outfile_append_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_APPEND && cur->filename)
			check_and_open_file(command, cur,
				O_WRONLY | O_CREAT | O_APPEND, &fd);
		cur = cur->next;
	}
	apply_fd_to_stdio(fd, STDOUT_FILENO, "dup2 append", command);
}


/*
** Les fonctions ci-dessous sont conservées pour compatibilité
** mais ne devraient plus être utilisées directement
*
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



static int	open_and_check_infile(t_redirect *cur, t_command *command, int fd)
{
	if (fd != -1)
		close(fd);
	check_permission(command, 0);
	fd = open(cur->filename, O_RDONLY);
	if (fd == -1)
		ft_exit_free(cur->filename, EXIT_FAILURE, command);
	return (fd);
}

void	infile_redirection(t_command *command)
{
	t_redirect	*cur;
	int			fd;

	cur = command->redir;
	fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_IN && cur->filename)
			fd = open_and_check_infile(cur, command, fd);
		cur = cur->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_exit_free("dup2 input", EXIT_FAILURE, command);
		close(fd);
	}
}*/
