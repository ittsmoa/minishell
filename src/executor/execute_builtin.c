#include "../../includes/minishell.h"

int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (builtin_env(shell));
	return (1);
}