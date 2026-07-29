/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 01:20:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	finish_fork(t_cmd *cmd, t_pipeline *pipeline, int pipe_fd[2])
{
	if (pipeline->prev_fd != -1)
		close(pipeline->prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	pipeline->prev_fd = pipe_fd[0];
	pipeline->started++;
	close_command_fds(cmd);
}

static int	fork_command(t_shell *shell, t_cmd *head, t_cmd *cmd,
		t_pipeline *pipeline)
{
	int	pipe_fd[2];

	init_pipe_fds(pipe_fd);
	if (cmd->next && pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pipeline->pids[pipeline->started] = fork();
	if (pipeline->pids[pipeline->started] == -1)
		return (close_pipeline_fds(NULL, pipe_fd[0]), close(pipe_fd[1]),
			perror("fork"), 1);
	if (pipeline->pids[pipeline->started] == 0)
	{
		set_child_signals();
		if (prepare_command_redirections(cmd))
			exit_pipeline_child(shell, head, pipeline, 1);
		if (setup_pipeline_fds(cmd, pipeline, pipe_fd))
			exit_pipeline_child(shell, head, pipeline, 1);
		close_other_command_fds(head, cmd);
		run_pipeline_child(shell, head, cmd, pipeline);
	}
	finish_fork(cmd, pipeline, pipe_fd);
	return (0);
}

static int	run_commands(t_shell *shell, t_cmd *head, t_pipeline *pipeline)
{
	t_cmd	*current;
	int		failed;

	current = head;
	failed = 0;
	while (current && !failed)
	{
		failed = fork_command(shell, head, current, pipeline);
		if (!failed)
			current = current->next;
	}
	close_pipeline_fds(current, pipeline->prev_fd);
	return (failed);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	t_pipeline	pipeline;
	int			failed;

	if (init_pipeline(shell, &pipeline, count_pipeline_commands(cmd)))
		return (1);
	set_wait_signals();
	failed = run_commands(shell, cmd, &pipeline);
	shell->exit_status = wait_pipeline(&pipeline);
	set_interactive_signals();
	free(pipeline.pids);
	if (failed)
		shell->exit_status = 1;
	return (shell->exit_status);
}
