/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 19:05:54 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 19:05:54 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_exit_value(char *arg, int *status)
{
	unsigned long long	value;
	unsigned long long	limit;
	int					sign;
	int					i;

	value = 0;
	sign = 1;
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	limit = 9223372036854775807ULL;
	if (sign == -1)
		limit = 9223372036854775808ULL;
	while (arg[i])
	{
		if (value > (limit - (arg[i] - '0')) / 10)
			return (1);
		value = value * 10 + (arg[i] - '0');
		i++;
	}
	if (sign == -1)
		*status = (unsigned char)(0 - (value % 256));
	else
		*status = (unsigned char)(value % 256);
	return (0);
}

static void	exit_cleanup(t_shell *shell, t_cmd *cmd, int status)
{
	free_cmd(cmd);
	free_envp(shell->envp);
	rl_clear_history();
	exit(status);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = shell->exit_status;
	write(1, "exit\n", 5);
	if (cmd->argv[1] && (!is_numeric_arg(cmd->argv[1])
			|| parse_exit_value(cmd->argv[1], &status)))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_cleanup(shell, cmd, 2);
	}
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_cleanup(shell, cmd, status);
	return (status);
}
