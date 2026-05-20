#include "../includes/minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
		free_split(cmd->argv, -1);
}

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
	cmd.argv = ft_split(line, ' ');
	cmd.next = NULL;
	cmd.outfile = -1; // tempppp
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
	return (shell.exit_status);
}