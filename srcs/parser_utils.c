/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:19:55 by sdossa            #+#    #+#             */
/*   Updated: 2025/10/27 19:34:21 by sdossa           ###   ########.fr       */
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
