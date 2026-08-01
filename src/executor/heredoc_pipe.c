/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/08/01 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_heredoc_io(t_heredoc_io *io)
{
	if (io->data[0] != -1)
		close(io->data[0]);
	if (io->data[1] != -1)
		close(io->data[1]);
	if (io->ready[0] != -1)
		close(io->ready[0]);
	if (io->ready[1] != -1)
		close(io->ready[1]);
}

int	init_heredoc_io(t_heredoc_io *io)
{
	init_pipe_fds(io->data);
	init_pipe_fds(io->ready);
	io->pid = -1;
	if (pipe(io->data) == -1)
		return (perror("pipe"), 1);
	if (pipe(io->ready) == -1)
	{
		close_heredoc_io(io);
		return (perror("pipe"), 1);
	}
	return (0);
}

void	wait_heredoc_writer(pid_t pid)
{
	int	result;

	if (pid <= 0)
		return ;
	result = waitpid(pid, NULL, 0);
	while (result == -1 && errno == EINTR)
		result = waitpid(pid, NULL, 0);
}

static int	failed_heredoc(t_shell *shell, t_heredoc_io *io)
{
	int	status;

	close(io->data[0]);
	if (waitpid(io->pid, &status, 0) == -1)
	{
		set_interactive_signals();
		return (perror("waitpid"), shell->exit_status = 1, 1);
	}
	report_signal_status(status);
	set_interactive_signals();
	shell->exit_status = get_process_status(status);
	if (shell->exit_status == 0)
		shell->exit_status = 1;
	return (1);
}

int	finish_heredoc_io(t_shell *shell, t_redir *redir, t_heredoc_io *io)
{
	ssize_t	result;
	char	ready;

	close(io->data[1]);
	close(io->ready[1]);
	result = read(io->ready[0], &ready, 1);
	while (result == -1 && errno == EINTR)
		result = read(io->ready[0], &ready, 1);
	close(io->ready[0]);
	if (result != 1 || ready != 1)
		return (failed_heredoc(shell, io));
	set_interactive_signals();
	redir->heredoc_fd = io->data[0];
	redir->heredoc_pid = io->pid;
	return (0);
}
