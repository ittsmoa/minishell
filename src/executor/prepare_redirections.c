/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 20:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/25 20:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_redir_file(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (redir->type == APPEND)
		return (open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644));
	ft_putstr_fd("minishell: heredoc is not connected yet\n", 2);
	return (-1);
}

static void	set_redir_fd(t_cmd *cmd, t_redir *redir, int fd)
{
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
	{
		if (cmd->infile != -1)
			close(cmd->infile);
		cmd->infile = fd;
	}
	else
	{
		if (cmd->outfile != -1)
			close(cmd->outfile);
		cmd->outfile = fd;
	}
}

static int	prepare_one_command_redirs(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		fd = open_redir_file(redir);
		if (fd == -1)
		{
			if (redir->type != HEREDOC)
				perror(redir->file);
			return (1);
		}
		set_redir_fd(cmd, redir, fd);
		redir = redir->next;
	}
	return (0);
}

int	prepare_command_redirections(t_cmd *cmd)
{
	return (prepare_one_command_redirs(cmd));
}
