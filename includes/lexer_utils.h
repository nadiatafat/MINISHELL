/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:21:19 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/13 14:48:51 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

int		token_len(char *line);
char	*copy_token(char *line, int len);
void	free_tokens(char **tokens);
int	handle_quotes_and_ops(char *line);

#endif
