#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_cmd	cmd;
	char	*args[] = {"echo", "hello", "bro", NULL};

	(void)argc;
	(void)argv;
	shell.envp = copy_envp(envp);
	shell.exit_status = 0;
	cmd.argv = args;
	cmd.next = NULL;
	execute(&shell, &cmd);
	set_env_value(&shell.envp, "PWD", "/test");
	printf("PWD = %s\n", get_env_value(shell.envp, "PWD"));
	free_envp(shell.envp);
	return (shell.exit_status);
}