/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:45:09 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/28 23:43:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_validation(t_redir *redir)
{
	while (redir)
	{
		if (!redir->file || !ft_is_redir(redir->type))
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	cmd_validation(t_cmd *cmd)
{
	if (!cmd)
		return (1);
	while (cmd)
	{
		if (redir_validation(cmd->redirs))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
