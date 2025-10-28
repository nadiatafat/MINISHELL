/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_escape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 07:18:35 by sdossa            #+#    #+#             */
/*   Updated: 2025/10/27 15:01:06 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include "lexer_escape.h"

/*
** Gère char échappés à l'intérieur de single quotes.
** Si on est dans des guillemets dbls et qu'on trouve un '\',
on ignore le caractère suivant.
** Return la nouvelle position après traitement de l'échappement.
*/
int	handle_escape_in_quotes(char *line, int len, char quote)
{
	if (quote == '"' && line[len] == '\\' && line[len + 1])
		return (len + 2);
	return (len + 1);
}

/*
** Compte les char à l'intérieur des quotes en gérant les échappements.
** Parcourt depuis l'ouverture jusqu'à la fermeture des quotes.
** Retourne la longueur totale ou -1 si les quotes ne sont pas fermés.
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
