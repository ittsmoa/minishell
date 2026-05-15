#include "../includes/minishell.h"

static void	child_process(t_shell *shell, t_cmd *cmd)
{
	char	*path;

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

int	execute_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		child_process(shell, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}
