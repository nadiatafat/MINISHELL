/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:38:52 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/10 01:16:46 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_REDIR_UTILS_H
# define PARSER_REDIR_UTILS_H

int	count_argv_tokens(char **tokens, int start, int end);
int	fill_argv(char **tokens, int start, int end, char **argv);
int	extract_redir(char **tokens, int start, int end, t_redirect **redir);

#endif
