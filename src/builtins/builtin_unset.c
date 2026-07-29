/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:08:57 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 02:05:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		remove_env_value(&shell->envp, cmd->argv[i]);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}
