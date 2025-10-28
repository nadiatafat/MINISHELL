/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:52:35 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/26 17:20:37 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_VARS_H
# define EXPAND_VARS_H

# include "minishell.h"

typedef struct s_expand_ctx
{
	char	**env;
	int		last_exit_code;
}	t_expand_ctx;

int		count_tokens_for_expansion(char **tokens);
char	**expand_tokens(char **tokens, t_expand_ctx *ctx);
char	*expand_token(char *token, t_expand_ctx *ctx);
char	*process_token_variables(char *result, t_expand_ctx *ctx);

#endif