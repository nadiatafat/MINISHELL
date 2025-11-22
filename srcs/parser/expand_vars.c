/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:50:31 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/21 13:17:45 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_vars.h"
#include "expand_utils.h"
#include "lexer_utils.h"

/*
** Compte les tokens dans le tab pour l'expansion; le parcourt jusqu'au
** 1er pointeur NULL. Return le nb total de tokens à traiter.
*/
int	count_tokens_for_expansion(char **tokens)
{
	int	token_count;

	token_count = 0;
	while (tokens[token_count])
		token_count++;
	return (token_count);
}

static int	check_has_quotes(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '"')
		|| ft_strchr(token, '\x02') || ft_strchr(token, '\x03')
		|| ft_strchr(token, '\x04'))
		return (1);
	return (0);
}

static int	count_expanded_tokens(char **tokens, t_expand_ctx *ctx)
{
	char	*temp;
	char	**split;
	int		i;
	int		count;
	int		k;

	i = -1;
	count = 0;
	while (tokens[++i])
	{
		temp = expand_token(tokens[i], ctx);
		if (!temp)
			return (-1);
		if (temp[0] && !check_has_quotes(tokens[i]) && ft_strchr(temp, ' '))
		{
			split = ft_split(temp, ' ');
			k = 0;
			while (split && split[k])
			{
				if (split[k][0])
					count++;
				k++;
			}
			free_tokens(split);
		}
		else if (temp[0])
			count++;
		free(temp);
	}
	return (count);
}

static int	process_token_loop(char **tokens, char **expanded,
	t_expand_ctx *ctx, int max_tokens)
{
	char	*temp;
	int		i;
	int		j;
	int		has_q;

	i = -1;
	j = 0;
	while (tokens[++i])
	{
		has_q = check_has_quotes(tokens[i]);
		temp = expand_token(tokens[i], ctx);
		if (!temp)
			return (-1);
		j = process_expanded_token(expanded, j, temp, has_q, max_tokens);
		if (j == -1 || j >= max_tokens)
			return (-1);
	}
	return (j);
}

/*
** Expanse les tokens d'un tab en appliquant les substitutions.
** Alloue 1 nouveau tab et traite chaque token individuellement.
** Return le tab expansé ou NULL en cas d'erreur.
*/
char	**expand_tokens(char **tokens, t_expand_ctx *ctx)
{
	char	**expanded;
	int		j;
	int		max_tokens;

	if (!tokens || !ctx)
		return (NULL);
	max_tokens = count_expanded_tokens(tokens, ctx);
	if (max_tokens == -1)
		return (NULL);
	max_tokens += 5;
	expanded = ft_calloc(sizeof(char *), max_tokens + 1);
	if (!expanded)
		return (NULL);
	j = process_token_loop(tokens, expanded, ctx, max_tokens);
	if (j == -1)
		return (free_tokens(expanded), NULL);
	expanded[j] = NULL;
	return (expanded);
}

/*
** Expanse le tilde (~) en début de token vers le répertoire HOME.
** Gère ~ seul ou suivi d'un /. Return token expansé ou original.
*/
static char	*expand_tilde(char *token, t_expand_ctx *ctx)
{
	char	*home;
	char	*result;

	if (!token || token[0] != '~')
		return (ft_strdup(token));
	if (token[0] == '~' && (token[1] == '\0' || token[1] == '/'))
	{
		home = get_env_value("HOME", ctx->env);
		if (!home)
			return (ft_strdup(token));
		if (token[1] == '\0')
			result = ft_strdup(home);
		else
			result = ft_strjoin(home, token + 1);
		free(home);
		return (result);
	}
	return (ft_strdup(token));
}

/*
** Expanse un token unique en traitant les var qu'il contient.
** Gère les tokens spé (commençant par \x01) et ceux sans var.
** Return token expansé ou NULL si erreur d'alloc.
*/
char	*expand_token(char *token, t_expand_ctx *ctx)
{
	char	*result;

	if (token && token[0] == '\x01')
		return (ft_strdup(token + 1));
	if (!token)
		return (NULL);
	result = expand_tilde(token, ctx);
	if (!result)
		return (NULL);
	return (process_token_variables(result, ctx));
}

/*
** Nettoie les marqueurs d'échappement \x02 d'une chaîne.
** Parcourt la chaîne et supprime tous les marqueurs trouvés.
*/
char	*clean_final_marker(char *str)
{
	char	*clean;
	int		i;
	int		j;

	if (!str)
		return (str);
	if (str[0] != '\x01')
		return (str);
	clean = malloc(ft_strlen(str));
	if (!clean)
		return (str);
	i = 1;
	j = 0;
	while (str[i])
		clean[j++] = str[i++];
	clean[j] = '\0';
	free(str);
	return (clean);
}


/*
** Nettoie les marqueurs d'échappement \x02 d'une chaîne.
** Parcourt la chaîne et supprime tous les marqueurs trouvés.
*
char	*clean_final_marker(char *str)
{
	int	i;

	if (!str || str[0] != '\x01')
		return (str);
	i = 0;
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}*/

char	*clean_escape_markers(char *result)
{
	int		i;
	int		j;
	int		has_marker;

	i = 0;
	j = 0;
	has_marker = 0;
	while (result[i])
	{
		if (result[i] == '\x02' || result[i] == '\x03'
			|| result[i] == '\x04')
		{
			has_marker = 1;
			i++;
		}
		else
			result[j++] = result[i++];
	}
	result[j] = '\0';
	if (has_marker && (ft_strcmp(result, "|") == 0 || ft_strcmp(result, "<") == 0
			|| ft_strcmp(result, ">") == 0 || ft_strcmp(result, "<<") == 0
			|| ft_strcmp(result, ">>") == 0))
	{
		result[1] = result[0];
		result[0] = '\x01';
		result[2] = '\0';
	}
	return (result);
}
