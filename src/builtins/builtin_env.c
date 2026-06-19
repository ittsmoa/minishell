#include "../../includes/minishell.h"

int	builtin_env(t_shell *shell)
{
	int	i;

	if (!shell || !shell->envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}
