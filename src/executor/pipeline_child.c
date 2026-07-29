/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 01:30:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 01:50:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_command_child(t_shell *shell, t_cmd *head, char *path, int status)
{
	free(path);
	free_cmd(head);
	free_envp(shell->envp);
	rl_clear_history();
	exit(status);
}

void	exit_pipeline_child(t_shell *shell, t_cmd *head,
		t_pipeline *pipeline, int status)
{
	free(pipeline->pids);
	exit_command_child(shell, head, NULL, status);
}

void	run_pipeline_child(t_shell *shell, t_cmd *head, t_cmd *cmd,
		t_pipeline *pipeline)
{
	char	*path;
	int		status;

	if (!cmd->argv || !cmd->argv[0])
		exit_pipeline_child(shell, head, pipeline, 0);
	if (is_builtin(cmd->argv[0]))
	{
		shell->child_mode = 1;
		status = execute_builtin(shell, cmd);
		exit_pipeline_child(shell, head, pipeline, status);
	}
	path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!path)
		exit_pipeline_child(shell, head, pipeline,
			print_command_error(cmd->argv[0]));
	execve(path, cmd->argv, shell->envp);
	if (errno == ENOEXEC)
	{
		status = execute_shell_script(shell, cmd, path);
		exit_pipeline_child(shell, head, pipeline, status);
	}
	status = get_execve_error_status();
	perror(cmd->argv[0]);
	free(path);
	exit_pipeline_child(shell, head, pipeline, status);
}
