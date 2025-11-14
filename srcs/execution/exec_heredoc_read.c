/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:31:26 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/14 16:13:03 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Comparer avec \n
static int	is_limiter_match(char *line, char *limiter_n)
{
	size_t	len;

	if (ft_strcmp(line, limiter_n) == 0)
		return (1);
	len = ft_strlen(limiter_n);
	if (len > 0 && limiter_n[len - 1] == '\n')
	{
		if (ft_strncmp(line, limiter_n, len - 1) == 0)
			return (1);
	}
	return (0);
}

// Écrire avec \n
static void	write_line_to_fd(char *line, int tmpfile_fd)
{
	ft_putstr_fd(line, tmpfile_fd);
	ft_putstr_fd("\n", tmpfile_fd);
}

/*
** Affiche un prompt "pipe heredoc>" et lit l'entrée utilisateur ligne par ligne
** jusqu'à atteindre le 'limiter' (par exemple : EOF, STOP, etc.)
** Chaque ligne est écrite dans le fichier temporaire correspondant.
*/
void	read_heredoc_content(char *limiter_n, int tmpfile_fd)
{
	char	*line;

	while (1)
	{
		line = readline("pipe heredoc> ");
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		if (is_limiter_match(line, limiter_n))
		{
			free(line);
			break ;
		}
		write_line_to_fd(line, tmpfile_fd);
		free(line);
	}
}
