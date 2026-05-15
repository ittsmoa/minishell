#include "../../includes/minishell.h"

int builtin_pwd(void)
{
    char    cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("pwd");
        return 1;
    }
    printf("%s\n", cwd);
    return 0;
}