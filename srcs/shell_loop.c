/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:26:20 by sdossa            #+#    #+#             */
/*   Updated: 2025/10/30 08:15:35 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand_vars.h"
#include "lexer.h"
#include "lexer_utils.h"
#include "node_cmd.h"
#include "parser.h"
#include "print_ast.h"
#include "shell_loop.h"
#include "syntax_check.h"
#include "syntax_validation.h"

/*
** Lit la saisie utilisateur avec readline.
** Affiche le prompt "minishell$ " et attend une entrée.
** Ajoute la ligne à l'historique si elle n'est pas vide.
*/
static char	*read_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && *line != '\0')
		add_history(line);
	return (line);
}

/*
** Prépare les tokens pour l'exec (lexing, validation, expansion).
** Fait l'analyse lexicale, check la syntaxe et expanse les var.
** Return 1 en cas de succès, 0 et msg si erreur.
*/
static int	prepare_tokens(char *line, char ***expanded_tokens,
t_mother_shell *shell)
{
	char			**tokens;
	t_expand_ctx	ctx;

	tokens = lexer_split(line);
	if (!tokens)
	{
		printf("Lexer error : quotes not closed or failed malloc\n");
		return (0);
	}
	if (!validate_syntax(tokens))
	{
		printf("Syntax error\n");
		free_tokens(tokens);
		return (0);
	}
	ctx.env = shell->env;
	ctx.last_exit_code = shell->last_status;
	*expanded_tokens = expand_tokens(tokens, &ctx);
	free_tokens(tokens);
	if (!*expanded_tokens)
		return (0);
	return (1);
}

/*
** Traite une ligne de cmd complète. Prépare les tokens, construit l'AST et
** l'affiche pour debug. Free tte la mémoire allouée après traitement.
*/
static void	process_line(char *line, t_mother_shell *shell)
{
	char	**expanded_tokens;
	t_node	*ast;

	if (!prepare_tokens(line, &expanded_tokens, shell))
		return ;
	ast = parse_tokens(expanded_tokens);
	if (ast)
	{
		print_ast(ast, 0);
		free_node(ast);
	}
	free_tokens(expanded_tokens);
}

/*
** Boucle principale du shell.
** Lit en continu les cmd utilisateur jusqu'à EOF ou exit.
** Traite chaque ligne non vide et gère la sortie propre du programme.
*/
void	shell_loop(t_mother_shell *shell)
{
	char	*line;

	while (1)
	{
		line = read_input();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		process_line(line, shell);
		free(line);
	}
}
