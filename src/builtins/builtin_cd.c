/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 11:16:02 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 11:16:02 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_error(char *path)
{
	write(2, "minishell: cd: ", 15);
	perror(path);
	return (1);
}

static char	*get_cd_path(t_shell *shell, t_cmd *cmd)
{
	char	*home;

	if (!cmd->argv[1])
	{
		home = get_env_value(shell->envp, "HOME");
		if (!home)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		return (home);
	}
	return (cmd->argv[1]);
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	oldpwd[1024];
	char	newpwd[1024];
	char	*path;

	path = get_cd_path(shell, cmd);
	if (!path)
		return (1);
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (cd_error("getcwd"));
	if (chdir(path) == -1)
		return (cd_error(path));
	if (!getcwd(newpwd, sizeof(newpwd)))
		return (cd_error("getcwd"));
	set_env_value(&shell->envp, "OLDPWD", oldpwd);
	set_env_value(&shell->envp, "PWD", newpwd);
	shell->exit_status = 0;
	return (0);
}