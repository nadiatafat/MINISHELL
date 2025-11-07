/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:51:23 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/07 15:12:28 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_vars.h"
#include "expand_utils.h"

/*
** Remplace une variable dans 1 chaîne par sa valeur.
** Divise la chaine en 3: avant, valeur, aprè, puis les concatene.
** Return la new chaîne ou la chaîne originale si erreur.
*/
char	*replace_variable(char *str, int start, int len, char *value)
{
	char	*before;
	char	*after;
	char	*result;

	if (!str || !value)
		return (str);
	before = ft_substr(str, 0, start);
	after = ft_strdup(str + start + len);
	if (!before || !after)
	{
		free(before);
		free(after);
		return (str);
	}
	result = join_three_strings(before, value, after);
	free(before);
	free(after);
	if (!result)
		return (str);
	return (result);
}

/*
** Joint 3 chaînes en 1: strjoin concatene s1+s2 puis le result avec s3.
** Return la chaîne finale ou NULL si erreur d'alloc.
*/
char	*join_three_strings(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

/*
** Récupère la valeur d'une var selon son nom. Cas speciale '$?':
** return code de retour (last_exit_code). Autres var: recherche
** dans l'env. Return la valeur allouee ou NULL si inexistante.
*/
char	*get_variable_value(char *var_name, t_expand_ctx *ctx)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(ctx->last_exit_code));
	return (get_env_value(var_name, ctx->env));
}

/*
** Traite une var spécifique à une position donnée dans la chaîne.
** Extrait le nom de la var, récupère sa valeur et effectue le remplacement.
** Return la chaîne modifiée ou la chaîne originale si échec.
*/
char	*process_variable(char *str, int pos, t_expand_ctx *ctx)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	var_name = get_var_name(str, pos + 1);
	if (!var_name)
		return (str);
	var_value = get_variable_value(var_name, ctx);
	result = replace_variable(str, pos, ft_strlen(var_name) + 1, var_value);
	free(var_name);
	free(var_value);
	return (result);
}

/*
** Traite ttes les var d'un token de manière itérative.
** Parcourt la chaîne, remplace chaque '$' trouvé hors single quotes.
** Recommence depuis debut après chaque remplacement pr gérer cas complexes.
*/
char	*process_token_variables(char *result, t_expand_ctx *ctx)
{
	char	*new_result;
	int		i;

	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1]
			&& !is_in_single_quotes(result, i))
		{
			new_result = process_variable(result, i, ctx);
			if (new_result != result)
			{
				free(result);
				result = new_result;
				i = 0;
				continue ;
			}
		}
		i++;
	}
	return (result);
}
