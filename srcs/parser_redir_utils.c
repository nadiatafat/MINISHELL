/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 03:59:34 by sdossa            #+#    #+#             */
/*   Updated: 2025/10/27 18:35:25 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_redir_utils.h"
#include "parser_redir.h"

/*
** Compte le nb de tokens "utiles" (non liés aux redirections).
** Pour savoir cb d’args doivent être alloués ds le tab argv du futur processus.
*/
int	count_argv_tokens(char **tokens, int start, int end)
{
	int	i;
	int	count;
	int	redir_type;

	i = start;
	count = 0;
	while (i < end)
	{
		redir_type = is_redirection(tokens[i]);
		if (redir_type)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

/*
** Copie dans argv uniquement les tokens non-redirections.
** Les opérateurs (<, >, >>, <<) et leurs cibles sont ignorés.
** Return 0 en cas de succès, -1 si une alloc échoue.
*/
int	fill_argv(char **tokens, int start, int end, char **argv)
{
	int	i;
	int	argv_index;
	int	redir_type;

	i = start;
	argv_index = 0;
	while (i < end)
	{
		redir_type = is_redirection(tokens[i]);
		if (redir_type)
			i += 2;
		else
		{
			argv[argv_index] = ft_strdup(tokens[i]);
			if (!argv[argv_index])
				return (-1);
			argv_index++;
			i++;
		}
	}
	argv[argv_index] = NULL;
	return (0);
}

/*
** Parcourt les tokens et construit la liste chaînée des redir.
** Chaque opérateur est associé à son fichier cible (ex: ">" out.txt).
** Return -1 si syntaxe invalide ou si une alloc échoue.
*/
int	extract_redir(char **tokens, int start, int end, t_redirect **redir)
{
	int				i;
	int				redir_type;
	t_redirect		*new_redir;

	i = start;
	*redir = NULL;
	while (i < end)
	{
		redir_type = is_redirection(tokens[i]);
		if (redir_type)
		{
			if (i + 1 >= end || !tokens[i + 1])
				return (-1);
			new_redir = new_redirection(redir_type, tokens[i + 1]);
			if (!new_redir)
				return (-1);
			add_redirect(redir, new_redir);
			i += 2;
		}
		else
			i++;
	}
	return (0);
}
