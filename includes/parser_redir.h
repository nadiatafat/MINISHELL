/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:39:08 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/10 01:47:51 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_REDIR_H
# define PARSER_REDIR_H

t_redirect	*new_redirection(int type, char *filename);
int			is_redirection(char *token);
void		add_redirect(t_redirect **head, t_redirect *new_redir);
void		free_redirections(t_redirect *redir);
int			parse_redir(char **tokens, int start, int end, t_command *cmd);

#endif
