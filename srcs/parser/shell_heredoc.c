/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:26:20 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/14 20:23:45 by sdossa           ###   ########.fr       */
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

extern volatile sig_atomic_t	g_sigint_received;

static void	process_heredoc_redir(t_redirect *r, int *heredoc_count)
{
	char	*tmp;
	int		fd;
	char	*original_filename;
	char	*limiter;

	tmp = ft_get_heredoc_filename((*heredoc_count)++);
	fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	original_filename = ft_strdup(r->filename);
	limiter = ft_strjoin(original_filename, "\n");
	free(original_filename);
	read_heredoc_content(limiter, fd);
	free(limiter);
	close(fd);
	free(r->filename);
	r->filename = tmp;
}

void	read_heredocs_before_exec(t_node *node)
{
	static int	heredoc_count = 0;
	t_redirect	*r;
	int			found_heredoc;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->command && node->command->redir)
	{
		r = node->command->redir;
		found_heredoc = 0;
		while (r)
		{
			if (r->type == REDIR_HEREDOC && !found_heredoc)
			{
				process_heredoc_redir(r, &heredoc_count);
				found_heredoc = 1;
			}
			r = r->next;
		}
	}
	else if (node->type == NODE_PIPE)
	{
		read_heredocs_before_exec(node->left);
		read_heredocs_before_exec(node->right);
	}
}
