/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:45:09 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/15 19:45:10 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_validation(t_redir *redir)
{
	if (!redir)
		return (0);
	while (redir)
	{
		if (!redir->file || redir->file[0] == '\0')
		{
			printf("redir type=%d file=%s\n", redir->type, redir->file);
			return (1);
		}
		else if (!ft_is_redir(redir->type))
		{
			printf("redir type=%d file=%s\n", redir->type, redir->file);
			return (1);
		}
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
		if (!cmd->redirs && !cmd->argv && !cmd->argv[0])
			return (1);
		if (redir_validation(cmd->redirs))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
