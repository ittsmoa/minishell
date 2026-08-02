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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

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
	int				quoted;
	int				skip;
	int				ambiguous;
	int				expanded;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
	int				delimiter_quoted;
	int				heredoc_fd;
	pid_t			heredoc_pid;
}	t_redir;

typedef struct s_heredoc_buffer
{
	char	*data;
	size_t	length;
	size_t	capacity;
}	t_heredoc_buffer;

typedef struct s_heredoc_io
{
	int		data[2];
	int		ready[2];
	pid_t	pid;
}	t_heredoc_io;

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
	int		child_mode;
}	t_shell;

typedef struct s_expand
{
	char		*current;
	char		*result;
	char		*mask;
	t_shell		*shell;
	t_token		*token;
	t_quote		quote;
}	t_expand;

typedef struct s_pipeline
{
	pid_t	*pids;
	int		prev_fd;
	int		started;
}	t_pipeline;

/* Executor */
int		execute(t_shell *shell, t_cmd *cmd);
int		execute_external(t_shell *shell, t_cmd *cmd);
int		execute_shell_script(t_shell *shell, t_cmd *cmd, char *path);
int		execute_builtin(t_shell *shell, t_cmd *cmd);
int		execute_pipeline(t_shell *shell, t_cmd *cmd);
void	exit_command_child(t_shell *shell, t_cmd *head, char *path,
			int status);
void	exit_pipeline_child(t_shell *shell, t_cmd *head,
			t_pipeline *pipeline, int status);
void	run_pipeline_child(t_shell *shell, t_cmd *head, t_cmd *cmd,
			t_pipeline *pipeline);
int		is_builtin(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);
int		setup_command_redirection(t_cmd *cmd, int saved_fds[2]);
void	restore_command_redirection(t_cmd *cmd, int saved_fds[2]);
void	close_command_fds(t_cmd *cmd);
int		apply_child_redirection(t_cmd *cmd);
int		get_process_status(int wait_status);
int		print_command_error(char *cmd);
int		get_execve_error_status(void);
void	init_pipe_fds(int pipe_fd[2]);
int		setup_pipeline_fds(t_cmd *cmd, t_pipeline *pipeline, int pipe_fd[2]);
void	close_other_command_fds(t_cmd *head, t_cmd *current);
void	close_pipeline_fds(t_cmd *cmd, int prev_fd);
int		init_pipeline(t_shell *shell, t_pipeline *pipeline, int count);
int		wait_pipeline(t_pipeline *pipeline);
int		count_pipeline_commands(t_cmd *cmd);
int		prepare_command_redirections(t_cmd *cmd);
int		prepare_heredocs(t_shell *shell, t_cmd *cmd);
int		init_heredoc_io(t_heredoc_io *io);
void	close_heredoc_io(t_heredoc_io *io);
int		finish_heredoc_io(t_shell *shell, t_redir *redir,
			t_heredoc_io *io);
void	wait_heredoc_writer(pid_t pid);
void	close_heredoc_fds(t_redir *redir);
void	print_heredoc_warning(char *delimiter);
int		append_heredoc_line(t_heredoc_buffer *buffer, char *line,
			t_redir *redir, t_shell *shell);
int		write_heredoc_buffer(int fd, t_heredoc_buffer *buffer);

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
t_redir	*new_redir(t_type type, char *file, int quoted);
int		add_redir(t_cmd *current, t_type type, char *file, int quoted);
t_cmd	*new_cmd(void);
t_cmd	*parse_tokens(t_token *tokens);
void	free_cmd(t_cmd *cmd);
void	free_argv(char **argv);
void	free_redir(t_redir *redir);
int		count_arg(char **arg);
int		cmd_validation(t_cmd *cmd);

/* Expander */
int		expand_tokens(t_token *tokens, t_shell *shell);
char	*extract_var_name(char *str);
int		expand_word(t_token *token, t_shell *shell, int expand_variables);
t_quote	quote_states(char **current, t_quote quote);
int		quote_check(char **current, t_quote *quote);
char	*expand_heredoc_line(char *line, t_shell *shell);
int		expand_append_text(t_expand *expand, char *text);
int		expand_append_char(t_expand *expand);
int		expand_append_status(t_expand *expand);
int		expand_append_variable(t_expand *expand);
int		split_expanded_word(t_token *token, char *mask);

/* Signals */
void	set_signal_handler(int signal_number, void (*handler)(int));
void	set_interactive_signals(void);
char	*read_command_line(char *prompt);
char	*read_heredoc_line(char *prompt);
void	set_wait_signals(void);
void	set_child_signals(void);
void	set_heredoc_signals(void);
void	report_signal_status(int status);

/* Debug */
void	print_redir(t_redir *redir);
char	*redir_name(t_type type);
void	print_argv(char **argv);
void	print_cmd(t_cmd *cmd);

#endif