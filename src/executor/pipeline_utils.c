/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 01:50:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipe_fds(int pipe_fd[2])
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
}

static void	close_pipe(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	init_pipe_fds(pipe_fd);
}

int	setup_pipeline_fds(t_cmd *cmd, t_pipeline *pipeline, int pipe_fd[2])
{
	if (pipeline->prev_fd != -1 && cmd->infile == -1
		&& dup2(pipeline->prev_fd, STDIN_FILENO) == -1)
		return (perror("dup2"), close_pipe(pipe_fd), 1);
	if (cmd->next && cmd->outfile == -1
		&& dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2"), close_pipe(pipe_fd), 1);
	if (pipeline->prev_fd != -1)
		close(pipeline->prev_fd);
	close_pipe(pipe_fd);
	return (apply_child_redirection(cmd));
}

void	close_other_command_fds(t_cmd *head, t_cmd *current)
{
	while (head)
	{
		if (head != current)
			close_command_fds(head);
		head = head->next;
	}
}

void	close_pipeline_fds(t_cmd *cmd, int prev_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	while (cmd)
	{
		close_command_fds(cmd);
		cmd = cmd->next;
	}
}
