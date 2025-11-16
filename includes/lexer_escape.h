/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_escape.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 07:13:25 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/16 18:19:24 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_ESCAPE_H
# define LEXER_ESCAPE_H

int		handle_escape_in_quotes(char *line, int len, char quote);
int		count_quote_content(char *line, char quote);
void	process_quotes_in_token(char *line, char *token, int *i, int *j);

#endif
