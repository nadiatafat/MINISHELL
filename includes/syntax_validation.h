/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 05:58:47 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/10 06:46:37 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_VALIDATION_H
# define SYNTAX_VALIDATION_H

int	is_pipe(char *token);
int	validate_redirections(char **tokens);
int	validate_pipes(char **tokens);
int	validate_syntax(char **tokens);

#endif
