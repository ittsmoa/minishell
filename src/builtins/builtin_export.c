/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *arg)
{
	int	i;

	if (!arg || !arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	env_has_key(char **envp, char *arg)
{
	int	len;
	int	i;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], arg, len)
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

static int	export_arg(t_shell *shell, char *arg)
{
	char	*key;
	char	*equal;
	int		status;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (!env_has_key(shell->envp, arg))
			return (add_env_value(&shell->envp, arg));
		return (0);
	}
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (1);
	status = set_env_value(&shell->envp, key, equal + 1);
	if (status)
		status = add_env_value(&shell->envp, arg);
	free(key);
	return (status);
}

int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	status;

	if (!cmd->argv[1])
		return (print_export(shell));
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i]))
		{
			export_error(cmd->argv[i]);
			status = 1;
		}
		else if (export_arg(shell, cmd->argv[i]))
			status = 1;
		i++;
	}
	return (status);
}
