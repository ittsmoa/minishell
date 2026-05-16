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

int	builtin_exit(t_shell *shell)
{
	int	status;

	status = shell->exit_status;
	write(1, "exit\n", 5);
	free_envp(shell->envp);
	exit(status);
}