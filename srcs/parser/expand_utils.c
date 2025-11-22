/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:42:57 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/19 16:05:08 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_utils.h"

/*
** Check et parcourt la chaîne à la recherche d'1 var ('$')
** suivi d'1 char. Return 1 si var trouvée.
*/
int	has_variable(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (i > 0 && str[i - 1] == '\x02')
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Récupère la valeur d'une var d'env, la cherche ds le tab env et
** return sa valeur. Return chaîne vide si la var n'existe pas.
*/
char	*get_env_value(char *var_name, char **env)
{
	int		i;
	int		len;
	char	*value;

	if (!var_name || !env)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			value = ft_strdup(env[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}

/*
** Vérifie si une pos ds la chaîne est à l'intérieur de single quotes .
** Compte les single quotes non échappés jusqu'à la pos donnée.
** Return 1 si pos est entre guillemets simples.
*/
int	is_in_single_quotes(char *str, int pos)
{
	int	i;
	int	in_single;

	i = 0;
	in_single = 0;
	while (i < pos && str[i])
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			in_single = !in_single;
		i++;
	}
	return (in_single);
}

/*
** Gère cas spécial de variables ($?, $", $', etc.).
** Traite les var spé comme le code de retour et les char spéciaux.
** Return la valeur correspondante ou NULL si ce n'est pas un cas spécial.
*/
char	*handle_special_var_cases(char *str, int start)
{
	while (str[start] == '\x04')
		start++;
	if (str[start] == '?')
		return (ft_strdup("?"));
	if (str[start] == '"' || str[start] == '\'' || str[start] == '\0'
		|| str[start] == '\x03')
		return (ft_strdup(""));
	if (ft_isdigit(str[start]))
		return (ft_substr(str, start, 1));
	return (NULL);
}

char	*extract_varname(char *str, int start, int len)
{
	char	*name;
	int		i;
	int		j;

	name = malloc(len + 1);
	if (!name)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[start + i] != '\x04')
			name[j++] = str[start + i];
		i++;
	}
	name[j] = '\0';
	return (name);
}
