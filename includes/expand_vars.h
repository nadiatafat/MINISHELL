/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:52:35 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/16 18:30:19 by sdossa           ###   ########.fr       */
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
char	*clean_escape_markers(char *result);
char	*clean_final_marker(char *str);

char	*join_three_strings(char *s1, char *s2, char *s3);
char	*process_token_variables(char *result, t_expand_ctx *ctx);
int		process_single_var(char **result, int i, t_expand_ctx *ctx);

int		calculate_var_len_with_markers(char *str, int start, int var_name_len);
int		split_and_add_tokens(char **exp, int j, char *temp, int max);
int		process_expanded_token(char **exp, int j, char *temp, int has_q, int max);
char	*get_var_name(char *str, int start);
int		count_varname_len(char *str, int start);

#endif
