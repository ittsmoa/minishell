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

static void	close_pipe(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
}

static void	setup_pipeline_fds(t_cmd *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1 && cmd->infile == -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(1);
	}
	if (cmd->next && cmd->outfile == -1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	if (prev_fd != -1)
		close(prev_fd);
	close_pipe(pipe_fd);
	apply_child_redirection(cmd);
}

static void	close_other_command_fds(t_cmd *head, t_cmd *current)
{
	while (head)
	{
		if (head != current)
			close_command_fds(head);
		head = head->next;
	}
}

static void	run_pipeline_child(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		status;

	if (is_builtin(cmd->argv[0]))
	{
		status = execute_builtin(shell, cmd);
		exit(status);
	}
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
	{
		perror(cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, shell->envp);
	perror(cmd->argv[0]);
	free(path);
	exit(127);
}

static int	fork_pipeline_command(t_shell *shell, t_cmd *head, t_cmd *cmd,
		int *prev_fd, pid_t *pid)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->next && pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	*pid = fork();
	if (*pid == -1)
		return (close_pipe(pipe_fd), perror("fork"), 1);
	if (*pid == 0)
	{
		setup_pipeline_fds(cmd, *prev_fd, pipe_fd);
		close_other_command_fds(head, cmd);
		run_pipeline_child(shell, cmd);
	}
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
	close_command_fds(cmd);
	return (0);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	pid_t	*pids;
	t_cmd	*current;
	int		prev_fd;
	int		count;
	int		i;
	int		status;

	count = count_commands(cmd);
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
		return (1);
	prev_fd = -1;
	current = cmd;
	i = 0;
	while (current)
	{
		if (fork_pipeline_command(shell, cmd, current, &prev_fd, &pids[i]))
			return (free(pids), 1);
		current = current->next;
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	i = 0;
	while (i < count)
		waitpid(pids[i++], &status, 0);
	free(pids);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}
