/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:39:38 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/26 17:31:27 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int			find_next_pipe(char **tokens, int start);
t_command	*new_command(char **tokens, int start, int end);
t_node		*add_command_to_tree(t_node *root, char **tokens,
				int start, int end);
t_node		*parse_tokens(char **tokens);
t_node		*parse_pipe_sequence(char **tokens, int start);

#endif
