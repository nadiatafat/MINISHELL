/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_escape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 07:18:35 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/01 11:05:38 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include "lexer_escape.h"

/*
** Avance dans la ligne, gere les echappements dans dbl quotes.
** Si on trouve '\' ou '\\', saute 2 char (le \ et le suivant).
** Sinon saute 1 char. Return la nouvelle position.
*/
int	handle_escape_in_quotes(char *line, int len, char quote)
{
	if (quote == '"' && line[len] == '\\' && line[len + 1])
		return (len + 2);
	return (len + 1);
}

/*
** Compte la len totale d'un token quoté (avec quotes).
** Gere les échappements via handle_escape_in_quotes.
** Return len totale ou -1 si quote fermante manquante.
*/
int	count_quote_content(char *line, char quote)
{
	int	len;

	len = 1;
	while (line[len] && line[len] != quote)
		len = handle_escape_in_quotes(line, len, quote);
	if (!line[len])
		return (-1);
	return (len + 1);
}
