/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:39:38 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/08 14:06:16 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

t_command	*new_command(char **tokens, int start, int end);
t_node		*add_command_to_tree(t_node *root, char **tokens,
				int start, int end);
t_node		*parse_tokens(char **tokens);
t_node		*parse_pipe_sequence(char **tokens, int start);

#endif
