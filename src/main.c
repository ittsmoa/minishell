#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	cmd;
	char	*exit_args[] = {"exit", NULL};

	(void)argc;
	(void)argv;
	shell.envp = copy_envp(envp);
	shell.exit_status = 0;
	cmd.argv = exit_args;
	cmd.next = NULL;
	execute(&shell, &cmd);
	free_envp(shell.envp);
	return (shell.exit_status);
}