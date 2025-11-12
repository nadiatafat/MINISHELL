/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:31:26 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/12 20:04:21 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** Affiche un prompt "pipe heredoc>" et lit l'entrée utilisateur ligne par ligne
** jusqu'à atteindre le 'limiter' (par exemple : EOF, STOP, etc.)
** Chaque ligne est écrite dans le fichier temporaire correspondant.
*/
static void	read_heredoc_content(char *limiter_n, int tmpfile_fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		if (ft_strncmp(line, limiter_n, ft_strlen(limiter_n)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, tmpfile_fd);
		free(line);
	}
}

/*
** Ouvre un fichier selon le mode demandé.
** open_flag == 0 → écriture (O_TRUNC)
** open_flag == 1 → lecture
*/
static int	ft_open_file(char *path, int open_flag, t_command *command)
{
	int	fd;

	if (open_flag == 0)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit_free(path, EXIT_FAILURE, command);
	return (fd);
}

/*
** Génère un nom de fichier temporaire unique : /tmp/heredoc_X
** X = index du heredoc courant
*/
static char	*ft_get_heredoc_filename(int index)
{
	char	*nb;
	char	*path;
	char	*tmp;

	nb = ft_itoa(index);
	if (!nb)
		return (NULL);
	tmp = ft_strjoin("/tmp/heredoc_", nb);
	free(nb);
	if (!tmp)
		return (NULL);
	path = ft_strdup(tmp);
	free(tmp);
	return (path);
}

/*
** Crée et écrit un fichier temporaire pour un heredoc donné.
** Si c'est le dernier heredoc, ouvre aussi le fichier en lecture
** pour le rediriger plus tard sur STDIN.
*/
static int	create_tmp_file(t_command *command, t_redirect *cur, char *tmp_path, int tmpfile_fd)
{
	char	*limiter_n;
	int		write_fd;

	write_fd = ft_open_file(tmp_path, 0, command);
	limiter_n = ft_strjoin(cur->filename, "\n");
	if (!limiter_n)
		ft_exit_free("malloc heredoc limiter", EXIT_FAILURE, command);
	read_heredoc_content(limiter_n, write_fd);
	free(limiter_n);
	close(write_fd);
	if (!cur->next || cur->next->type != REDIR_HEREDOC)
	{
		if (tmpfile_fd != -1)
			close(tmpfile_fd);
		tmpfile_fd = ft_open_file(tmp_path, 1, command);
	}
	return (tmpfile_fd);
}


/*
** Gère tous les heredocs d'une commande :
** - crée un fichier temporaire pour chacun (/tmp/heredoc_X)
** - lit leur contenu depuis stdin
** - garde le dernier heredoc ouvert en lecture (pour stdin)
** - supprime les fichiers temporaires (unlink)
*/
int	get_heredoc(t_command *command)
{
	t_redirect	*cur;
	int			i;
	int			tmpfile_fd;
	char		*tmp_path;

	cur = command->redir;
	i = 0;
	tmpfile_fd = -1;
	while (cur)
	{
		if (cur->type == REDIR_HEREDOC)
		{
			tmp_path = ft_get_heredoc_filename(i++);
			if (!tmp_path)
				ft_exit_free("heredoc filename", EXIT_FAILURE, command);
			tmpfile_fd = create_tmp_file(command, cur, tmp_path, tmpfile_fd);
			unlink(tmp_path);
			free(tmp_path);
		}
		cur = cur->next;
	}
	return (tmpfile_fd);
}
