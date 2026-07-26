/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 19:48:18 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/25 20:10:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*build_command(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmd;
	t_env	*env;

	tokens = lexer_line(line);
	if (!tokens)
		return (NULL);
	if (!ft_is_valid(tokens, shell))
		return (free_tokens(&tokens), NULL);
	env = read_env(shell->envp);
	if (!env)
		return (free_tokens(&tokens), NULL);
	expand_tokens(tokens, env, shell);
	free_env(env);
	cmd = parse_tokens(tokens);
	free_tokens(&tokens);
	if (!cmd || cmd_validation(cmd))
		return (free_cmd(cmd), NULL);
	return (cmd);
}

static int	parse_and_execute(t_shell *shell, char *line)
{
	t_cmd	*cmd;

	cmd = build_command(shell, line);
	if (!cmd)
		return (shell->exit_status = 1, 1);
	if (!cmd->next && prepare_command_redirections(cmd))
	{
		shell->exit_status = 1;
		free_cmd(cmd);
		return (1);
	}
	execute(shell, cmd);
	free_cmd(cmd);
	return (0);
}

static int	handle_line(t_shell *shell, char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (1);
	}
	if (line[0] == '\0')
		return (0);
	add_history(line);
	parse_and_execute(shell, line);
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
