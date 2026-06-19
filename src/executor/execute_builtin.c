#include "../../includes/minishell.h"

static int	run_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (builtin_env(shell));
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (builtin_export(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (builtin_unset(shell, cmd));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (builtin_exit(shell, cmd));
	return (1);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	int	status;
	int	saved_fds[2];

	if (setup_command_redirection(cmd, saved_fds))
	{
		close_command_fds(cmd);
		shell->exit_status = 1;
		return (1);
	}
	status = run_builtin(shell, cmd);
	fflush(stdout);
	restore_command_redirection(cmd, saved_fds);
	shell->exit_status = status;
	return (status);
}
