/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 19:52:32 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/25 19:52:46 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_quote
{
	UNQUOTED,
	SINGEL,
	DOUBLE,
}	t_quote;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
	int				is_delimeter_quoted;
}	t_redir;

typedef struct s_cmd
{
	t_redir			*redirs;
	char			**argv;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
}	t_shell;

typedef struct s_pipeline
{
	pid_t	*pids;
	int		prev_fd;
	int		started;
}	t_pipeline;

/* Executor */
int		execute(t_shell *shell, t_cmd *cmd);
int		execute_external(t_shell *shell, t_cmd *cmd);
void	execute_shell_script(t_shell *shell, t_cmd *cmd, char *path);
int		execute_builtin(t_shell *shell, t_cmd *cmd);
int		execute_pipeline(t_shell *shell, t_cmd *cmd);
int		is_builtin(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);
int		setup_command_redirection(t_cmd *cmd, int saved_fds[2]);
void	restore_command_redirection(t_cmd *cmd, int saved_fds[2]);
void	close_command_fds(t_cmd *cmd);
void	apply_child_redirection(t_cmd *cmd);
int		get_process_status(int wait_status);
int		print_command_error(char *cmd);
int		get_execve_error_status(void);
void	init_pipe_fds(int pipe_fd[2]);
void	setup_pipeline_fds(t_cmd *cmd, t_pipeline *pipeline, int pipe_fd[2]);
void	close_other_command_fds(t_cmd *head, t_cmd *current);
void	close_pipeline_fds(t_cmd *cmd, int prev_fd);
int		init_pipeline(t_shell *shell, t_pipeline *pipeline, int count);
int		wait_pipeline(t_pipeline *pipeline);
int		prepare_command_redirections(t_cmd *cmd);

/* Builtins */
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(t_cmd *cmd);
int		builtin_env(t_shell *shell, t_cmd *cmd);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_export(t_shell *shell, t_cmd *cmd);
int		print_export(t_shell *shell);
int		builtin_unset(t_shell *shell, t_cmd *cmd);
int		exit_is_numeric_arg(char *arg);
int		parse_exit_value(char *arg, int *status);
int		builtin_exit(t_shell *shell, t_cmd *cmd);

/* Environment */
char	**copy_envp(char **envp);
void	free_envp(char **envp);
char	*get_env_value(char **envp, char *key);
int		set_env_value(char ***envp, char *key, char *value);
int		add_env_value(char ***envp, char *new_var);
int		remove_env_value(char ***envp, char *key);
void	free_split(char **res, int size);

/* Lexer */
t_token	*new_token(t_type t, char *v);
t_token	*lexer_line(char *line);
void	add_back(t_token **head, t_token *new_tok);
void	print_l(t_token **head);
void	free_tokens(t_token **tokens);
int		ft_is_operation(char c);
int		ft_is_space(char c);
int		error_msg(char *token, t_shell *shell);
int		ft_is_valid(t_token *tokens, t_shell *shell);
int		quote_error(void);
int		handle_redir_right(char *line, int i, t_token **head);
int		handle_redir_left(char *line, int i, t_token **head);
int		has_ampersand(char *s);
int		ft_is_redir(t_type type);
char	*remove_quotes(char *argv);
int		add_back_pipe(t_token **head, t_token *new_token);

/* Parser */
int		add_argv(t_cmd *current, char *word);
void	redir_add_back(t_redir **head, t_redir *new);
t_redir	*new_redir(t_type type, char *file);
int		add_redir(t_cmd *current, t_type type, char *file);
t_cmd	*new_cmd(void);
t_cmd	*parse_tokens(t_token *tokens);
void	free_cmd(t_cmd *cmd);
void	free_argv(char **argv);
void	free_redir(t_redir *redir);
int		count_arg(char **arg);
int		cmd_validation(t_cmd *cmd);

/* Expander */
int		parse_env(char *envp, char **key, char **value);
t_env	*read_env(char **envp);
char	*get_value_of_env(t_env *env, char *key);
void	free_env(t_env *env);
void	expand_tokens(t_token *tokens, t_env *env, t_shell *shell);
char	*extract_var_name(char *str);
void	expand_word(t_token *tokens, t_env *env, t_shell *shell);
t_quote	quote_states(char **current, t_quote quote);
void	appeand_exit_status(char **current, char **result, t_shell *shell);
int		quote_check(char **current, t_quote *quote);
void	appeand_string(char **result, char *str);

/* Debug */
void	print_redir(t_redir *redir);
char	*redir_name(t_type type);
void	print_argv(char **argv);
void	print_cmd(t_cmd *cmd);
void	print_env(t_env *env);

#endif