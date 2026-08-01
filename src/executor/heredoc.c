/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 00:42:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/08/01 15:51:17 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc(t_shell *shell, t_redir *redir, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
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
		if (write_heredoc_line(fd, line, redir, shell))
			return (free(line), 1);
		free(line);
	}
}

static void	heredoc_child(t_shell *shell, t_cmd *head, t_redir *redir,
		int fds[2])
{
	int	status;

	close(fds[0]);
	set_heredoc_signals();
	status = read_heredoc(shell, redir, fds[1]);
	close(fds[1]);
	free_cmd(head);
	free_envp(shell->envp);
	rl_clear_history();
	exit(status);
}

static int	wait_heredoc(t_shell *shell, pid_t pid, int fds[2])
{
	int	status;
	int	exit_status;

	close(fds[1]);
	if (waitpid(pid, &status, 0) == -1)
	{
		close(fds[0]);
		set_interactive_signals();
		return (perror("waitpid"), shell->exit_status = 1, 1);
	}
	report_signal_status(status);
	set_interactive_signals();
	exit_status = get_process_status(status);
	if (exit_status)
	{
		close(fds[0]);
		shell->exit_status = exit_status;
		return (1);
	}
	return (0);
}

static int	collect_heredoc(t_shell *shell, t_cmd *head, t_redir *redir)
{
	int		fds[2];
	pid_t	pid;

	if (open_heredoc_file(fds))
		return (shell->exit_status = 1, 1);
	set_wait_signals();
	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		set_interactive_signals();
		return (perror("fork"), shell->exit_status = 1, 1);
	}
	if (pid == 0)
		heredoc_child(shell, head, redir, fds);
	if (wait_heredoc(shell, pid, fds))
		return (1);
	redir->heredoc_fd = fds[0];
	return (0);
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
