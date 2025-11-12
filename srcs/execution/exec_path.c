/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:26:27 by nadgalle          #+#    #+#             */
/*   Updated: 2025/11/07 14:54:51 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

/*
** Vérifie que le chemin donné correspond à un exécutable valide :
** - existence du fichier
** - non répertoire
** - droits d'exécution
** En cas d’erreur, quitte le programme avec un code adapté.
*/
void	ft_check_path(char *path, t_command *command)
{
	struct stat	file_stat;

	if (!ft_strchr(path, '/'))
	{
		if (access(path, F_OK) != 0)
			ft_exit_error(path, strerror(errno), 1, command);
	}
	else
	{
		if (access(path, F_OK) != 0)
			ft_exit_error(path, strerror(errno), 127, command);
	}
	if (stat(path, &file_stat) != -1)
	{
		if (S_ISDIR(file_stat.st_mode))
			ft_exit_error(path, "Is a directory", 126, command);
	}
	if (access(path, X_OK) != 0)
		ft_exit_error(path, "Permission denied", 126, command);
}

/*
** Récupère la variable PATH depuis l'environnement et la découpe
** en un tableau de chemins, séparés par ':'.
** Exemple : "PATH=/bin:/usr/bin" → ["bin", "usr/bin", NULL]
*/
char	**get_path_tab(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
			i++;
	if (env[i])
	{
		paths = ft_split(env[i] + 5, ':');
		return (paths);
	}
	return (NULL);
}

/*
** Construit un chemin complet à partir d’un dossier et d’une commande :
** Exemple : path="/bin", cmd="ls" → "/bin/ls"
*/
char	*ft_join_path(char *cmd, char *path)
{
	char	*path_tmp;
	char	*joined_path;

	path_tmp = ft_strjoin(path, "/");
	joined_path = ft_strjoin(path_tmp, cmd);
	free(path_tmp);
	return (joined_path);
}

/*
** Cherche le chemin absolu d’une commande :
** - Si la commande contient déjà un '/', on la retourne telle quelle.
** - Sinon, on parcourt chaque dossier du PATH pour trouver le binaire.
** Renvoie le chemin trouvé ou NULL si la commande est introuvable.
*/
char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	else
	{
		paths = get_path_tab(env);
		if (!paths)
			return (NULL);
		i = 0;
		while (paths[i])
		{
			path = ft_join_path(cmd, paths[i++]);
			if (access(path, F_OK) == 0)
			{
				ft_free_tab(paths);
				return (path);
			}
			free(path);
		}
		ft_free_tab(paths);
	}
	return (NULL);
}
