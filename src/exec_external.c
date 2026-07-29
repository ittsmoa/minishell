/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 01:50:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_child_redirection(t_cmd *cmd)
{
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		close(cmd->outfile);
		cmd->outfile = -1;
	}
	return (0);
}

int	execute_shell_script(t_shell *shell, t_cmd *cmd, char *path)
{
	char	**argv;
	int		status;
	int		i;

	argv = malloc(sizeof(char *) * (count_arg(cmd->argv) + 2));
	if (!argv)
		return (free(path), 1);
	argv[0] = "/bin/sh";
	argv[1] = path;
	i = 1;
	while (cmd->argv[i])
	{
		argv[i + 1] = cmd->argv[i];
		i++;
	}
	argv[i + 1] = NULL;
	execve(argv[0], argv, shell->envp);
	status = get_execve_error_status();
	perror(argv[0]);
	free(argv);
	free(path);
	return (status);
}

static void	child_process(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		status;

	set_child_signals();
	if (apply_child_redirection(cmd))
		exit_command_child(shell, cmd, NULL, 1);
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
		exit_command_child(shell, cmd, NULL,
			print_command_error(cmd->argv[0]));
	execve(path, cmd->argv, shell->envp);
	if (errno == ENOEXEC)
	{
		status = execute_shell_script(shell, cmd, path);
		exit_command_child(shell, cmd, NULL, status);
	}
	status = get_execve_error_status();
	perror(cmd->argv[0]);
	exit_command_child(shell, cmd, path, status);
}

static int	wait_external(t_shell *shell, t_cmd *cmd, pid_t pid)
{
	int	status;

	close_command_fds(cmd);
	if (waitpid(pid, &status, 0) == -1)
	{
		set_interactive_signals();
		perror("waitpid");
		shell->exit_status = 1;
		return (1);
	}
	report_signal_status(status);
	set_interactive_signals();
	shell->exit_status = get_process_status(status);
	return (shell->exit_status);
}

int	execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	set_wait_signals();
	pid = fork();
	if (pid == -1)
	{
		set_interactive_signals();
		perror("fork");
		close_command_fds(cmd);
		shell->exit_status = 1;
		return (1);
	}
	if (pid == 0)
		child_process(shell, cmd);
	return (wait_external(shell, cmd, pid));
}
