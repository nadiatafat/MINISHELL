/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:10:40 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/01 15:10:56 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "lexer_utils.h"

/*
** Parcourt la ligne et check que ts les quotes sont bien fermés.
** Retourne 1 si la syntaxe est valide.
*/
int	check_closed_quotes(char *line)
{
	char	quote;

	while (*line)
	{
		if (*line == '\'' || *line == '"')
		{
			quote = *line;
			line++;
			while (*line && *line != quote)
				line++;
			if (!*line)
				return (0);
		}
		line++;
	}
	return (1);
}

/*
** Compte le nb de tokens dans la ligne de cmd. Ignore les espaces et
** compte chaque élément séparé. Return le nb total de tokens à allouer.
*/
static int	count_tokens(char *line)
{
	int	count;
	int	len;

	count = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line)
		{
			len = token_len(line);
			count++;
			line += len;
		}
	}
	return (count);
}

/*
** Remplit le tab de tokens en copiant chaque élément.
** Parcourt la ligne, ignore les espaces et copie chaque token.
** Return le tab rempli ou NULL si erreur d'alloc.
*/
static char	**fill_tokens(char *line, char **tokens)
{
	int	i;
	int	len;

	i = 0;
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line)
		{
			len = token_len(line);
			tokens[i] = copy_token(line, len);
			if (!tokens[i])
				return (NULL);
			i++;
			line += len;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

/*
** Divise 1 ligne de cmd en tokens (analyse lexicale). Check la validité
** des guillemets puis alloue et remplit le tab.
** Return le tab de tokens ou NULL si erreur.
*/
char	**lexer_split(char *line)
{
	char	**tokens;

	if (!check_closed_quotes(line))
		return (NULL);
	tokens = malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	if (!fill_tokens(line, tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
