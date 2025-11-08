/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_escape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 07:18:35 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/08 20:26:15 by sdossa           ###   ########.fr       */
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
	{
		return (len + 2);
	}
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
	{
		len = handle_escape_in_quotes(line, len, quote);
	}
	if (!line[len])
	{
		return (-1);
	}
	return (len + 1);
}

/*
** Traite les échappements et copie le contenu entre quotes.
** Gère les marqueurs \x01 et \x02 selon le type de quote et échappements.
*/
static void	process_quoted_content(char *line, int len, char *token, char quote)
{
	int	i;
	int	j;

	j = 0;
	if (quote == '\'')
		token[j++] = '\x01';
	i = 1;
	while (i < len - 1)
	{
		if (quote == '"' && line[i] == '\\')
			i = handle_escape_in_double_quotes(line, i, token, &j);
		else
			token[j++] = line[i++];
	}
	token[j] = '\0';
}

/*
** Traite les échappements et copie le contenu entre quotes.
** Gère les marqueurs \x01 et \x02 selon le type de quote et échappements.
*/
int	handle_escape_in_double_quotes(char *line, int i, char *token, int *j)
{
	if (line[i + 1] == '"' || line[i + 1] == '\\')
	{
		i++;
		token[(*j)++] = line[i++];
	}
	else if (line[i + 1] == '$')
	{
		i++;
		token[(*j)++] = '\x02';
		token[(*j)++] = line[i++];
	}
	else
		token[(*j)++] = line[i++];
	return (i);
}

/*
** Copie le contenu d'un token entre quotes.
** Single quotes: marqueur \x01 + pas d'expansion.
** Return le token sans les quotes de délimitation.
*/
char	*copy_quoted(char *line, int len)
{
	char	quote;
	char	*token;

	quote = line[0];
	token = malloc(len);
	if (!token)
		return (NULL);
	process_quoted_content(line, len, token, quote);
	return (token);
}
