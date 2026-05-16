/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:08:57 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 16:08:57 by moatieh          ###   ########.fr       */
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
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_error(char *arg)
{
	write(2, "minishell: unset: `", 19);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i]))
		{
			unset_error(cmd->argv[i]);
			status = 1;
		}
		else
			remove_env_value(&shell->envp, cmd->argv[i]);
		i++;
	}
	shell->exit_status = status;
	return (status);
}