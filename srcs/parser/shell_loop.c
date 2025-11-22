/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:26:20 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/22 12:05:25 by sdossa           ###   ########.fr       */
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
/* static  */char	*read_input(t_mother_shell *shell)
{
	shell->line = readline("minishell$ ");

	if (shell->line && *shell->line != '\0')
		add_history(shell->line);
	return (shell->line);
}

/*
** Prépare les tokens pour l'exec (lexing, validation, expansion).
** Fait l'analyse lexicale, check la syntaxe et expanse les var.
** Return 1 en cas de succès, 0 et msg si erreur.
*/
/* static  */int	prepare_tokens(char *line, char ***expanded_tokens,
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
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		shell->last_status = 2;
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
/* static  */void	process_line(char *line, t_mother_shell *shell)
{
	char	**expanded_tokens;
	//char	*tmp_file;

	if (shell->last_expanded_tokens)
	{
		free_tokens(shell->last_expanded_tokens);
		shell->last_expanded_tokens = NULL;
	}
	if (!prepare_tokens(line, &expanded_tokens, shell))
		return ;
	shell->last_expanded_tokens = expanded_tokens;
	shell->ast = parse_tokens(expanded_tokens);
	if (shell->ast)
	{
		read_heredocs_before_exec(shell->ast);
		execute_ast(shell->ast, shell);
		free_node(shell->ast);
		shell->ast = NULL;
	}
	free_tokens(expanded_tokens);
	shell->last_expanded_tokens = NULL;
	return ;
}



/*
** Traite une ligne de cmd complète. Prépare les tokens, construit l'AST et
** l'affiche pour debug. Free tte la mémoire allouée après traitement.
*/
/*static  void	process_line(char *line, t_mother_shell *shell)
/{
	char	**expanded_tokens;

	if (shell->last_expanded_tokens)
	{
		free_tokens(shell->last_expanded_tokens);
		shell->last_expanded_tokens = NULL;
	}
	if (!prepare_tokens(line, &expanded_tokens, shell))
		return ;
	shell->last_expanded_tokens = expanded_tokens;
	shell->ast = parse_tokens(expanded_tokens);
	if (shell->ast)
	{
		read_heredocs_before_exec(shell->ast);
		execute_ast(shell->ast, shell);
		free_node(shell->ast);
		shell->ast = NULL;
	}
	free_tokens(expanded_tokens);
	shell->last_expanded_tokens = NULL;
	return ;
}*/

/* static  */void	handle_signal_status(t_mother_shell *shell)
{
	if (g_sigint_received == SIGINT)
	{

		shell->last_status = 130;
		g_sigint_received = 0;
	}
}

/*
** Boucle principale du shell.
** Lit en continu les cmd utilisateur jusqu'à EOF ou exit.
** Traite chaque ligne non vide et gère la sortie propre du programme.
*/
void	shell_loop(t_mother_shell *shell)
{
	while (1)
	{
		read_input(shell);
		handle_signal_status(shell);
		if (!shell->line)
		{
			if (shell->last_expanded_tokens)
			{
				free_tokens(shell->last_expanded_tokens);
				shell->last_expanded_tokens = NULL;
			}
			//rl_clear_history();
			return ;
		}
		if (*shell->line == '\0')
		{
			free(shell->line);
			continue ;
		}
		process_line(shell->line, shell);
		free(shell->line);
	}
}


/*
** Boucle principale du shell.
** Lit en continu les cmd utilisateur jusqu'à EOF ou exit.
** Traite chaque ligne non vide et gère la sortie propre du programme.
*
void	shell_loop(t_mother_shell *shell)
{
	while (1)
	{
		read_input(shell);
		handle_signal_status(shell);
		if (!shell->line)
		{
			if (shell->last_expanded_tokens)
			{
				free_tokens(shell->last_expanded_tokens);
				shell->last_expanded_tokens = NULL;
			}
			return ;
		}
		if (*shell->line == '\0')
		{
			free(shell->line);
			continue ;
		}
		process_line(shell->line, shell);
		free(shell->line);
	}
}*/
