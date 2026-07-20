/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_cleanup(t_shell *shell, t_cmd *cmd, int status)
{
	free_cmd(cmd);
	free_envp(shell->envp);
	rl_clear_history();
	exit(status);
}

static void	exit_numeric_error(t_shell *shell, t_cmd *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_cleanup(shell, cmd, 2);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = shell->exit_status;
	write(1, "exit\n", 5);
	if (cmd->argv[1] && (!exit_is_numeric_arg(cmd->argv[1])
			|| parse_exit_value(cmd->argv[1], &status)))
		exit_numeric_error(shell, cmd);
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_cleanup(shell, cmd, status);
	return (status);
}
