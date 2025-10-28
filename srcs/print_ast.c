/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 00:20:03 by sdossa            #+#    #+#             */
/*   Updated: 2025/10/27 19:43:04 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print_ast.h"

/*
** Affiche récursivement l'AST avec indentation.
** Parcourt l'arbre et délègue l'affichage selon le type de nœud.
** Utilise la profondeur pour créer une représentation hiérarchique.
*/
void	print_ast(t_node *node, int depth)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		print_command_node(node, depth);
	else if (node->type == NODE_PIPE)
		print_pipe_node(node, depth);
}

/*
** Affiche un nœud de cmd avec ses args.
** Utilise l'indentation basée sur la profondeur dans l'arbre.
** Affiche tous les args de la cmd sur une ligne.
*/
void	print_command_node(t_node *node, int depth)
{
	int	i;

	printf("%*sCOMMAND:", depth * 2, "");
	i = 0;
	while (node->command->argv[i])
	{
		printf(" %s", node->command->argv[i]);
		i++;
	}
	printf("\n");
}

/*
** Affiche un nœud pipe et ses sous-arbres.
** Affiche d'abord l'indicateur PIPE puis récurse sur les enfants.
** Incrémente la profondeur pour l'indentation des sous-nœuds.
*/
void	print_pipe_node(t_node *node, int depth)
{
	printf("%*sPIPE\n", depth * 2, "");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
