/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:49:44 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/16 17:42:24 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

# include "expand_vars.h"

int		has_variable(char *str);
char	*get_env_value(char *var_name, char **env);
int		is_in_single_quotes(char *str, int pos);
char	*handle_special_var_cases(char *str, int start);
char	*extract_varname(char *str, int start, int len);

#endif
