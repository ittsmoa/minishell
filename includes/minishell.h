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

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"

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

int	execute(t_shell *shell, t_cmd *cmd);
int	execute_external(t_shell *shell, t_cmd *cmd);
int	builtin_pwd(void);
int	builtin_echo(t_cmd *cmd);
int	builtin_env(t_shell *shell);
char	*get_env_value(char **envp, char *name);
char	*get_cmd_path(char *cmd, char **envp);
int	is_builtin(char *cmd);
int	execute_builtin(t_shell *shell, t_cmd *cmd);

#endif