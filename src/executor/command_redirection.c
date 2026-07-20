/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	save_fd(int fd, int *saved_fd)
{
	*saved_fd = dup(fd);
	if (*saved_fd == -1)
	{
		perror("dup");
		return (1);
	}
	return (0);
}

static int	redirect_fd(int from_fd, int to_fd, int *saved_fd)
{
	if (save_fd(to_fd, saved_fd))
		return (1);
	if (dup2(from_fd, to_fd) == -1)
	{
		perror("dup2");
		close(*saved_fd);
		*saved_fd = -1;
		return (1);
	}
	return (0);
}

int	setup_command_redirection(t_cmd *cmd, int saved_fds[2])
{
	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (!cmd)
		return (0);
	if (cmd->infile != -1
		&& redirect_fd(cmd->infile, STDIN_FILENO, &saved_fds[0]))
		return (1);
	if (cmd->outfile != -1
		&& redirect_fd(cmd->outfile, STDOUT_FILENO, &saved_fds[1]))
	{
		restore_command_redirection(cmd, saved_fds);
		return (1);
	}
	return (0);
}

void	restore_command_redirection(t_cmd *cmd, int saved_fds[2])
{
	if (saved_fds[0] != -1)
	{
		if (dup2(saved_fds[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(saved_fds[0]);
		saved_fds[0] = -1;
	}
	if (saved_fds[1] != -1)
	{
		if (dup2(saved_fds[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(saved_fds[1]);
		saved_fds[1] = -1;
	}
	close_command_fds(cmd);
}

void	close_command_fds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile != -1)
	{
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd && cmd->outfile != -1)
	{
		close(cmd->outfile);
		cmd->outfile = -1;
	}
}
