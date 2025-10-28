/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:36:57 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/10 02:34:08 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_CMD_H
# define NODE_CMD_H

t_node	*new_command_node(t_command *cmd);
t_node	*new_pipe_node(t_node *left, t_node *right);
void	free_node(t_node *node);
void	free_command(t_command *cmd);

#endif
