/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	apply_child_redirection(t_cmd *cmd)
{
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(cmd->outfile);
		cmd->outfile = -1;
	}
}

static void	child_process(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	int		status;

	apply_child_redirection(cmd);
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
		exit(print_command_error(cmd->argv[0]));
	execve(path, cmd->argv, shell->envp);
	status = get_execve_error_status();
	perror(cmd->argv[0]);
	free(path);
	exit(status);
}

int	execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close_command_fds(cmd);
		shell->exit_status = 1;
		return (1);
	}
	if (pid == 0)
		child_process(shell, cmd);
	close_command_fds(cmd);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		shell->exit_status = 1;
		return (1);
	}
	shell->exit_status = get_process_status(status);
	return (shell->exit_status);
}
