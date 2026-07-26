/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void	run_pipeline_child(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		status;

	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(shell, cmd));
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
		exit(print_command_error(cmd->argv[0]));
	execve(path, cmd->argv, shell->envp);
	if (errno == ENOEXEC)
		execute_shell_script(shell, cmd, path);
	status = get_execve_error_status();
	perror(cmd->argv[0]);
	free(path);
	exit(status);
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
		if (prepare_command_redirections(cmd))
			exit(1);
		setup_pipeline_fds(cmd, pipeline, pipe_fd);
		close_other_command_fds(head, cmd);
		run_pipeline_child(shell, cmd);
	}
	if (pipeline->prev_fd != -1)
		close(pipeline->prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	pipeline->prev_fd = pipe_fd[0];
	pipeline->started++;
	close_command_fds(cmd);
	return (0);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	t_pipeline	pipeline;
	t_cmd		*current;
	int			failed;

	if (init_pipeline(shell, &pipeline, count_commands(cmd)))
		return (1);
	current = cmd;
	failed = 0;
	while (current && !failed)
	{
		failed = fork_command(shell, cmd, current, &pipeline);
		if (!failed)
			current = current->next;
	}
	close_pipeline_fds(current, pipeline.prev_fd);
	shell->exit_status = wait_pipeline(&pipeline);
	free(pipeline.pids);
	if (failed)
		shell->exit_status = 1;
	return (shell->exit_status);
}
