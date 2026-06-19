#include "../includes/minishell.h"

static int	handle_line(t_shell *shell, char *line)
{
	t_cmd	cmd;

	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	if (line[0] == '\0')
		return (0);
	add_history(line);
	cmd = temp_parse_line(line);
	if (!cmd.argv)
		return (0);
	execute(shell, &cmd);
	free_cmd(&cmd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	int		should_exit;

	(void)argc;
	(void)argv;
	shell.envp = copy_envp(envp);
	shell.exit_status = 0;
	should_exit = 0;
	while (!should_exit)
	{
		line = readline("minishell$ ");
		should_exit = handle_line(&shell, line);
		free(line);
	}
	free_envp(shell.envp);
	rl_clear_history();
	return (shell.exit_status);
}
