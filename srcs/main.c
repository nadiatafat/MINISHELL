/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:29:02 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/01 14:52:50 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "shell_loop.h"

volatile sig_atomic_t	g_sigint_received = 0;

extern void	rl_replace_line(const char *str, int n);

/*
** Gestionnaire de signal pour Ctrl-C (SIGINT).
** Affiche nouvelle ligne et redémarre l'invite de commande.
** Utilise readline pour maintenir l'état de l'interface utilisateur.
*/
static void	sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
** Initialise la struct principale du shell.
** Copie les var d'env et initialise les champs de base.
** Alloue la mémoire nécessaire pour l'env du shell.
*/
static void	init_shell(t_mother_shell *shell, char **envp)
{
	int	i;
	int	j;

	shell->ast = NULL;
	shell->last_status = 0;
	i = 0;
	while (envp[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		exit(1);
	j = 0;
	while (j < i)
	{
		shell->env[j] = ft_strdup(envp[j]);
		j++;
	}
	shell->env[i] = NULL;
}

/*
** Free tte la mémoire allouée pour la struct du shell.
** Free chaque var d'env puis le tab principal.
** Évite les fuites mémoire à la fermeture du programme ;).
*/
static void	free_shell(t_mother_shell *shell)
{
	int	i;

	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
	}
}

/*
** Configure les signaux, init le shell et lance la boucle principale.
** Nettoie la mémoire avant de terminer le programme.
*/
int	main(int argc, char **argv, char **envp)
{
	t_mother_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_bind_key('\t', rl_insert);
	shell_loop(&shell);
	free_shell(&shell);
	return (0);
}
