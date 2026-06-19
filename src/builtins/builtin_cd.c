/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 11:16:02 by moatieh           #+#    #+#             */
/*   Updated: 2026/06/15 01:36:42 by moatieh          ###   ########.fr       */
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
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home);
	}
	return (cmd->argv[1]);
}

static int	add_pwd_value(t_shell *shell, char *key, char *value)
{
	char	*prefix;
	char	*entry;
	int		status;

	prefix = ft_strjoin(key, "=");
	if (!prefix)
		return (1);
	entry = ft_strjoin(prefix, value);
	free(prefix);
	if (!entry)
		return (1);
	status = add_env_value(&shell->envp, entry);
	free(entry);
	return (status);
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	oldpwd[1024];
	char	newpwd[1024];
	char	*path;

	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = get_cd_path(shell, cmd);
	if (!path)
		return (1);
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (cd_error("getcwd"));
	if (chdir(path) == -1)
		return (cd_error(path));
	if (!getcwd(newpwd, sizeof(newpwd)))
		return (cd_error("getcwd"));
	if (set_env_value(&shell->envp, "OLDPWD", oldpwd))
	{
		if (add_pwd_value(shell, "OLDPWD", oldpwd))
			return (1);
	}
	if (set_env_value(&shell->envp, "PWD", newpwd))
	{
		if (add_pwd_value(shell, "PWD", newpwd))
			return (1);
	}
	return (0);
}
