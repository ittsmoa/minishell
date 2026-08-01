/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 10:12:32 by maradweh          #+#    #+#             */
/*   Updated: 2026/08/01 09:59:05 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp)
		free_envp(shell->envp);
	if (shell->cmd)
		free_cmd(shell->cmd);
}

// after add it appear leaks in herdoc
// ctrl d in heredoc
// 
