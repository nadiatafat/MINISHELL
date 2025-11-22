/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:26:20 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/22 11:34:14 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand_vars.h"
#include "lexer.h"
#include "lexer_utils.h"
#include "node_cmd.h"
#include "parser.h"
#include "print_ast.h"
#include "shell_loop.h"
#include "syntax_check.h"
#include "syntax_validation.h"

static int	init_heredoc_counter(int reset)
{
	static int	counter = 0;

	if (reset)
		counter = 0;
	return (counter++);
}

static void	process_heredoc_redir(t_redirect *r, char *tmp_file, int is_first)
{
	int		fd;
	char	*original_filename;
	char	*limiter;
	int		flags;

	if (is_first)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(tmp_file, flags, 0644);
	if (fd == -1)
		return ;
	original_filename = ft_strdup(r->filename);
	limiter = ft_strjoin(original_filename, "\n");
	free(original_filename);
	read_heredoc_content(limiter, fd);
	free(limiter);
	close(fd);
}

void	read_heredocs_before_exec(t_node *node)
{
	t_redirect	*r;
	t_redirect	*last_heredoc;
	char		*tmp_file;
	int			is_first;

	init_heredoc_counter(1);
	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->command && node->command->redir)
	{
		last_heredoc = NULL;
		r = node->command->redir;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
				last_heredoc = r;
			r = r->next;
		}
		if (!last_heredoc)
			return ;
		tmp_file = ft_get_heredoc_filename(init_heredoc_counter(0));
		r = node->command->redir;
		is_first = 1;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
			{
				process_heredoc_redir(r, tmp_file, is_first);
				is_first = 0;
				free(r->filename);
				r->filename = ft_strdup(tmp_file);
			}
			r = r->next;
		}
		free(tmp_file);
	}
	else if (node->type == NODE_PIPE)
	{
		read_heredocs_before_exec(node->left);
		read_heredocs_before_exec(node->right);
	}
}

