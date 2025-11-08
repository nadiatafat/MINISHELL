/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:54:07 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/08 14:03:53 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include "lexer_escape.h"

/*
** Détecte et gère les opérateurs doubles (>>, <<), simples (|, <, >)
** et quotes lors du parsing. Return la longueur de l'élément détecté.
*/
static int	handle_quotes_and_ops(char *line)
{
	if (*line == '>' && *(line + 1) == '>')
		return (2);
	if (*line == '<' && *(line + 1) == '<')
		return (2);
	if (*line == '|' || *line == '<' || *line == '>')
		return (1);
	if (*line == '\'' || *line == '"')
		return (count_quote_content(line, *line));
	return (0);
}

/*
** Calcule length d'un token dans ligne de commande.
** Traite d'abord les cas spéciaux (opérateurs, quotes).
** Sinon compte jusqu'au prochain délimiteur (espace, pipe, redir).
*/
int	token_len(char *line)
{
	int	len;
	int	s;

	if (!line || !*line)
		return (0);
	s = handle_quotes_and_ops(line);
	if (s)
		return (s);
	len = 0;
	while (line[len] && line[len] != ' ' && line[len] != '|'
		&& line[len] != '<' && line[len] != '>')
		len++;
	return (len);
}

/*
** Copie 1 token depuis la ligne de cmd, utilise copy_quoted pour
** tokens entre quotes. Sinon fait une copie simple du token.
*/
char	*copy_token(char *line, int len)
{
	char	*token;
	int		i;

	if ((line[0] == '"' || line[0] == '\'') && len >= 2)
		return (copy_quoted(line, len));
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = line[i];
		i++;
	}
	token[len] = '\0';
	return (token);
}

/*
** Free chaque token individuellement puis le tab lui-même.
** Check que le tab n'est pas NULL avant de procéder.
*/
void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
