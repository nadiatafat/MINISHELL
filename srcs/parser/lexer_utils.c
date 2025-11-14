/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:54:07 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/14 18:23:58 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"
#include "lexer_escape.h"

/*
** Détecte et gère les opérateurs doubles (>>, <<), simples (|, <, >)
** et quotes lors du parsing. Return la longueur de l'élément détecté.
*/
int	handle_quotes_and_ops(char *line)
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

static int	get_operator_len(char *line)
{
	if (*line == '|' || *line == '<' || *line == '>')
	{
		if ((*line == '>' && *(line + 1) == '>')
			|| (*line == '<' && *(line + 1) == '<'))
			return (2);
		return (1);
	}
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
	int	quote_len;
	int	op_len;

	if (!line || !*line)
		return (0);
	op_len = get_operator_len(line);
	if (op_len > 0)
		return (op_len);
	len = 0;
	while (line[len] && line[len] != ' ' && line[len] != '|'
		&& line[len] != '<' && line[len] != '>')
	{
		if (line[len] == '\'' || line[len] == '"')
		{
			quote_len = count_quote_content(&line[len], line[len]);
			if (quote_len == -1)
				return (-1);
			len += quote_len;
		}
		else
			len++;
	}
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
	int		j;

	token = malloc((len * 2) + 1);
	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (line[i] == '\'' || line[i] == '"')
			process_quotes_in_token(line, token, &i, &j);
		else
			token[j++] = line[i++];
	}
	token[j] = '\0';
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
