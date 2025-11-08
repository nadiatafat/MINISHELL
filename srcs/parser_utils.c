/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:19:55 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/08 20:29:53 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_utils.h"

/*
** Compte tokens restants à partir d'une position donnée.
** Parcourt le tab depuis la pos start jusqu'à la fin.
** Return le nb de tokens restants dans le tab.
*/
int	count_tokens_from(char **tokens, int start)
{
	int	count;

	count = 0;
	while (tokens[start + count])
		count++;
	return (count);
}

/*
** Trouve la pos du prochain pipe dans le tab de tokens.
** Parcourt les tokens depuis start jusqu'à trouver un "|".
** Return index du pipe ou -1 si aucun pipe.
*/
int	find_next_pipe(char **tokens, int start)
{
	int	i;

	i = start;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			return (i);
		i++;
	}
	return (-1);
}
