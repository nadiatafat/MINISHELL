/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:19:45 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/17 16:39:37 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "parser_redir.h"
#include "parser_utils.h"
#include "node_cmd.h"

/*
** Crée une struct t_command à partir des tokens[start...end-1].
** Alloue la struct, parse les redir et args.
** Return la cmd créée ou NULL en cas d'erreur.
*/
t_command	*new_command(char **tokens, int start, int end)
{
	int			result;
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->redir = NULL;
	cmd->argv = NULL;
	result = parse_redir(tokens, start, end, cmd);
	if (result == -1)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

/*
** Crée un nœud de cmd et le connecte à l'arbre existant.
** Si root est NULL, retourne directement le nœud de cmd.
** Sinon crée un nœud pipe pour connecter root et la nouvelle cmd.
*/
t_node	*add_command_to_tree(t_node *root, char **tokens, int start, int end)
{
	t_command	*cmd;
	t_node		*cmd_node;
	t_node		*pipe_node;

	cmd = new_command(tokens, start, end);
	if (!cmd)
		return (free_node(root), NULL);
	cmd_node = new_command_node(cmd);
	if (!cmd_node)
	{
		free_command(cmd);
		return (NULL);
	}
	if (!root)
		return (cmd_node);
	pipe_node = new_pipe_node(root, cmd_node);
	if (!pipe_node)
	{
		free_node(cmd_node);
		return (NULL);
	}
	return (pipe_node);
}

/*
** Fonction principale de parsing des tokens.
** Point d'entrée pour transformer les tokens en AST.
** Délègue le travail à parse_pipe_sequence.
*/
t_node	*parse_tokens(char **tokens)
{
	return (parse_pipe_sequence(tokens, 0));
}

/*
** Parse une séquence de cmd séparées par des pipes.
** Construit l'AST en traitant chaque cmd entre les pipes.
** Return la racine de l'arbre ou NULL si erreur.
*/
t_node	*parse_pipe_sequence(char **tokens, int start)
{
	t_node	*root;
	int		pipe_pos;
	int		end;

	root = NULL;
	while (tokens[start])
	{
		pipe_pos = find_next_pipe(tokens, start);
		if (pipe_pos == -1)
		{
			end = count_tokens_from(tokens, start);
			root = add_command_to_tree(root, tokens, start, start + end);
			break ;
		}
		root = add_command_to_tree(root, tokens, start, pipe_pos);
		if (!root)
			return (NULL);
		start = pipe_pos + 1;
	}
	return (root);
}
