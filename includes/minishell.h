/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 06:50:09 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/15 06:50:09 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                  Includes                                  */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

/* ************************************************************************** */
/*                                  Structs                                   */
/* ************************************************************************** */

typedef struct s_cmd
{
	char			**argv;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}	t_cmd;

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

/* ************************************************************************** */
/*                                 Executor                                   */
/* ************************************************************************** */

int		execute(t_shell *shell, t_cmd *cmd);
int		execute_external(t_shell *shell, t_cmd *cmd);
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

/* ************************************************************************** */
/*                                  Builtins                                  */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                               Environment                                  */
/* ************************************************************************** */

char	**copy_envp(char **envp);
void	free_envp(char **envp);
char	*get_env_value(char **envp, char *key);
int		set_env_value(char ***envp, char *key, char *value);
int		add_env_value(char ***envp, char *new_var);
int		remove_env_value(char ***envp, char *key);

void	free_split(char **res, int size);

// temppppppppppppp!!!!!!!!!!!!!!!!!!!!!!!!!
void	temp_init_cmd(t_cmd *cmd);
int		temp_is_pipe(char *arg);
int		temp_is_redirection(char *arg);
int		temp_parse_redirections(t_cmd *cmd);
int		temp_add_command_segment(t_cmd *head, t_cmd **tail,
			char **tokens, int start);
int		temp_pipe_error(void);
int		temp_parse_tokens(t_cmd *head, char **tokens);
t_cmd	temp_parse_line(char *line);
void	free_cmd(t_cmd *cmd);

#endif
