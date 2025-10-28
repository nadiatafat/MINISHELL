/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:49:44 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/26 17:33:00 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

# include "expand_vars.h"

int		has_variable(char *str);
char	*get_var_name(char *str, int start);
char	*get_env_value(char *var_name, char **env);
int		is_in_single_quotes(char *str, int pos);
char	*handle_special_var_cases(char *str, int start);
char	*replace_variable(char *str, int start, int len, char *value);
char	*join_three_strings(char *s1, char *s2, char *s3);
char	*get_variable_value(char *var_name, t_expand_ctx *ctx);
char	*process_variable(char *str, int pos, t_expand_ctx *ctx);

#endif