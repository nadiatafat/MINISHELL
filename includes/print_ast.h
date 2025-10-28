/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:40:02 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/10 00:52:04 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_AST_H
# define PRINT_AST_H

void	print_ast(t_node *node, int depth);
void	print_command_node(t_node *node, int depth);
void	print_pipe_node(t_node *node, int depth);

#endif
