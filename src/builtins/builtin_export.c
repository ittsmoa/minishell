/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 13:02:09 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 13:02:09 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || arg[0] == '=')
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
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
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

static int	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		printf("declare -x %s\n", shell->envp[i]);
		i++;
	}
	return (0);
}

static int	export_arg(t_shell *shell, char *arg)
{
	char	*key;
	char	*equal;
	int		ret;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (0);
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (1);
	if (get_env_value(shell->envp, key))
		ret = set_env_value(&shell->envp, key, equal + 1);
	else
		ret = add_env_value(&shell->envp, arg);
	free(key);
	return (ret);
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
	shell->exit_status = status;
	return (status);
}