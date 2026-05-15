#include "../../includes/minishell.h"

int	execute(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(shell, cmd));
	return (execute_external(shell, cmd));
}