/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 00:42:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 15:19:55 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc(t_shell *shell, t_redir *redir,
		t_heredoc_buffer *buffer)
{
	char	*line;

	while (1)
	{
		line = read_heredoc_line("> ");
		if (g_signal == SIGINT)
			return (free(line), 130);
		if (!line)
		{
			print_heredoc_warning(redir->file);
			return (0);
		}
		if (!ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1))
		{
			free(line);
			return (0);
		}
		if (append_heredoc_line(buffer, line, redir, shell))
			return (free(line), 1);
		free(line);
	}
}

static void	heredoc_child(t_shell *shell, t_cmd *head, t_redir *redir,
		t_heredoc_io *io)
{
	t_heredoc_buffer	buffer;
	char				ready;
	int					status;

	close(io->data[0]);
	close(io->ready[0]);
	g_signal = 0;
	set_heredoc_signals();
	buffer.data = NULL;
	buffer.length = 0;
	buffer.capacity = 0;
	status = read_heredoc(shell, redir, &buffer);
	set_signal_handler(SIGINT, SIG_IGN);
	if (g_signal == SIGINT)
		status = 130;
	ready = (status == 0);
	if (write(io->ready[1], &ready, 1) != 1)
		status = 1;
	close(io->ready[1]);
	if (!status)
		status = write_heredoc_buffer(io->data[1], &buffer);
	free(buffer.data);
	close(io->data[1]);
	exit_command_child(shell, head, NULL, status);
}

static int	collect_heredoc(t_shell *shell, t_cmd *head, t_redir *redir)
{
	t_heredoc_io	io;

	if (init_heredoc_io(&io))
		return (shell->exit_status = 1, 1);
	set_wait_signals();
	io.pid = fork();
	if (io.pid == -1)
	{
		close_heredoc_io(&io);
		set_interactive_signals();
		return (perror("fork"), shell->exit_status = 1, 1);
	}
	if (io.pid == 0)
		heredoc_child(shell, head, redir, &io);
	return (finish_heredoc_io(shell, redir, &io));
}

int	prepare_heredocs(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*head;
	t_redir	*redir;

	head = cmd;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC
				&& collect_heredoc(shell, head, redir))
				return (1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
