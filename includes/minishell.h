/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:28:09 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/12 20:19:07 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/*ENUMERATION TYPE*/

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN = 1,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/*STUCTURES*/

typedef struct s_redirect
{
	int					type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char		**argv;
	t_redirect	*redir;
}	t_command;

typedef struct s_node
{
	t_node_type		type;
	struct s_node	*left;
	struct s_node	*right;
	t_command		*command;
}	t_node;

/*MOTHER STRUCTURE*/

typedef struct s_mother_shell
{
	t_node	*ast;
	int		last_status;
	char	**env;
}	t_mother_shell;

/****************************************************************/
/*                       	FUNCTIONS                           */
/****************************************************************/

extern void	rl_replace_line(const char *str, int n);
extern volatile sig_atomic_t	g_sigint_received;

/****************************************************************/
/*              FONCTIONS BUILTINS                              */
/****************************************************************/

int	ft_tabchr_home(char **env);
int	tab_size(char **tab);
void	ft_cd(char **tokens, int *exit_status, char **env);
void	ft_cd_invalid_opt(char **tokens, int *exit_code, char **env);
void	ft_parse_flags(char **tokens, size_t *i, int *print_newline);
void	ft_print_tok(char **tokens, size_t i, int output_fd);
void	ft_echo(char **tokens, int output_fd);
char		*ft_strdup2(char *src, int n);
void		ft_env(char **envp, int output_fd);
char	**ft_minimal_env(char **envp);
void		ft_exit(char **tokens, int *exit_status);
void	ft_print_export(char **env, int output_fd);
void	ft_swap(char **s1, char **s2);
char		**ft_sort_env(char **env, int output_fd);
int	ft_extract_key_value(char *token, char **key, char **value);
int	ft_replace_env_var(char **envp, char *key, char *value);
int	ft_add_new_env_var(char ***envp, char *key, char *value);
int	ft_check_identifier(char **tokens, int *exit_status);
char	**ft_export(char **envp, char **tokens, int *exit_status, int fd);
void	ft_pwd(int output_fd, char **tokens, int *exit_code);
char	**ft_unset(char **envp, char **tokens, int *exit_status);
int	ft_check_option(int *exit_status, char **tokens);
char	**ft_duplicate_env(char **envp);
int			ft_isbuiltin(char *str);
void		ft_exebuiltin(char **tokens, char ***envp, int *exit, int fd);
int	ft_error_builtin(char *path, char *error, int error_code, int *exit_code);
int	ft_check_path_builtin(char *path, int *exit_code);
int	ft_check_redirection(t_command *command, int *exit_code);

void	ft_puterror(char *cmd, char *cmd2, char *error);
char **ft_add_to_array(char **arr, char *str);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size, int free_flag);
void ft_free_tab(char **tab);


/****************************************************************/
/*              FONCTIONS UTILITAIRES                           */
/****************************************************************/

/* Gestion HEREDOC */
int	get_heredoc(t_command *command);

/* Gestion PATH */
void	ft_check_path(char *path, t_command *command);
char	**get_path_tab(char **env);
char	*ft_join_path(char *cmd, char *path);
char	*get_path(char *cmd, char **env);

/* Gestion REDIRECTIONS */
void	infile_redirection(t_command *command);
void	heredoc_redirection(t_command *command);
void	outfile_truncate_redirection(t_command *command);
void	outfile_append_redirection(t_command *command);
int	handle_redirections(t_redirect *redir);
void	free_tokens(char **tokens);
//void	handle_child_redirection(t_command *command);
//void	handle_parent_redirection(t_command *command);

/* Gestion UTILS */
void	ft_exit_error(char *path, char *error, int code, t_command *cmd);
void	ft_free_command(t_command *command);
//void	ft_free_command(t_command *command);
void	ft_exit_free(char *msg, int status, t_command *cmd);
void	close_inherited_fds(void);
void	setup_signal_handling(void);

int	execute_ast(t_node *node, t_mother_shell *shell);

#endif
