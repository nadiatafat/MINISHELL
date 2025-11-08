/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_escape.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 07:13:25 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/08 20:29:36 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_ESCAPE_H
# define LEXER_ESCAPE_H

char	*copy_quoted(char *line, int len);
int		handle_escape_in_quotes(char *line, int len, char quote);
int		count_quote_content(char *line, char quote);
int		handle_escape_in_double_quotes(char *line, int i, char *token, int *j);

#endif
