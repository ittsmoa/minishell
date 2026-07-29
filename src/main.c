/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 19:48:18 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 01:25:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*build_command(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = lexer_line(line);
	if (!tokens)
	{
		shell->exit_status = 2;
		return (NULL);
	}
	if (!ft_is_valid(tokens, shell))
		return (free_tokens(&tokens), NULL);
	if (expand_tokens(tokens, shell))
		return (free_tokens(&tokens), NULL);
	cmd = parse_tokens(tokens);
	free_tokens(&tokens);
	if (!cmd || cmd_validation(cmd))
	{
		shell->exit_status = 1;
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

static int	parse_and_execute(t_shell *shell, char *line)
{
	t_cmd	*cmd;

	cmd = build_command(shell, line);
	if (!cmd)
		return (1);
	if (prepare_heredocs(shell, cmd))
		return (free_cmd(cmd), 1);
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

static int	is_ignored_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '\0' || *line == '#');
}

static int	handle_line(t_shell *shell, char *line)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	if (!line)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	if (is_ignored_line(line))
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
	if (!shell.envp)
		return (1);
	shell.exit_status = 0;
	shell.child_mode = 0;
	should_exit = 0;
	set_interactive_signals();
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
