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
# include "../libft/libft.h"

/* ************************************************************************** */
/*                                  Structs                                   */
/* ************************************************************************** */

typedef struct s_cmd
{
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
}	t_shell;

/* ************************************************************************** */
/*                                 Executor                                   */
/* ************************************************************************** */

int		execute(t_shell *shell, t_cmd *cmd);
int		execute_external(t_shell *shell, t_cmd *cmd);
int		execute_builtin(t_shell *shell, t_cmd *cmd);
int		is_builtin(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);

/* ************************************************************************** */
/*                                  Builtins                                  */
/* ************************************************************************** */

int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_env(t_shell *shell);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_export(t_shell *shell, t_cmd *cmd);
int		builtin_unset(t_shell *shell, t_cmd *cmd);
int		builtin_exit(t_shell *shell);

/* ************************************************************************** */
/*                               Environment                                  */
/* ************************************************************************** */

char	**copy_envp(char **envp);
void	free_envp(char **envp);
char	*get_env_value(char **envp, char *key);
int		set_env_value(char ***envp, char *key, char *value);
int		add_env_value(char ***envp, char *new_var);
int		remove_env_value(char ***envp, char *key);

#endif