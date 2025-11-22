/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 03:59:22 by sdossa            #+#    #+#             */
/*   Updated: 2025/10/27 19:29:10 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_redir.h"
#include "parser_redir_utils.h"
#include "lexer_utils.h"

/*
** Check si 1 token est un opérateur de redirection et le compare avec ts
** les opé de redir supportés. Return le type de redirection ou 0.
*/
int	is_redirection(char *token)
{
	int	i;

	if (!token)
		return (0);
	i = 0;
	while (token[i])
	{
		if (token[i] == '\x02' || token[i] == '\x03' || token[i] == '\x04')
			return (0);
		i++;
	}
	if (ft_strcmp(token, "<<") == 0)
		return (REDIR_HEREDOC);
	if (ft_strcmp(token, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	return (0);
}

/*
** Crée un nouveau nœud de redirection avec type et fichier cible.
** Alloue la struct et duplique le nom de fichier.
** Return la redir créée ou NULL si erreur d'alloc.
*/
t_redirect	*new_redirection(int type, char *filename)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

/*
** Ajoute une redir à la fin de la liste chaînée.
** Parcourt la liste jusqu'au dernier élément pour maintenir l'ordre.
** Gère cas où la liste est vide (1er élément).
*/
void	add_redirect(t_redirect **head, t_redirect *new_redir)
{
	t_redirect	*current;

	if (!head || !new_redir)
		return ;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

/*
** Free récursivement tte la liste des redir, le nom de fichier
** et la struct de chaque nœud.
** Parcourt la liste en sauvegardant le pointeur suivant.
*/
void	free_redirections(t_redirect *redir)
{
	t_redirect	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->filename);
		free(redir);
		redir = next;
	}
}

/*
** Parse les redir et sépare les args du tab argv.
** Compte et copie les tokens non-redirections dans argv.
** Extrait les redir dans une liste chaînée séparée.
*/
int	parse_redir(char **tokens, int start, int end, t_command *cmd)
{
	int	argv_count;

	argv_count = count_argv_tokens(tokens, start, end);
	cmd->argv = malloc(sizeof(char *) * (argv_count + 1));
	if (!cmd->argv)
		return (-1);
	if (fill_argv(tokens, start, end, cmd->argv) == -1)
	{
		free(cmd->argv);
		return (-1);
	}
	if (extract_redir(tokens, start, end, &cmd->redir) == -1)
	{
		free_tokens(cmd->argv);
		free_redirections(cmd->redir);
		return (-1);
	}
	return (argv_count);
}
