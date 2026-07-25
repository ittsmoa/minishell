/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 06:30:00 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/22 15:59:57 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_shell	shell;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	shell = (t_shell){0};
	shell.envp = read_env(envp);
	cmd = NULL;
	tokens = NULL;
	while (1)
	{
		printf("%s", "\x1b[31m");
		line = readline("minishell$ ");
		printf("%s", "\x1b[0m");
		if (!line)
		{
			free_cmd(cmd);
			free_tokens(&tokens);
			rl_clear_history();
			break ;
		}
		if (*line)
			add_history(line);
		// printf("%s\n",line);
		tokens = lexer_line(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		if (!ft_is_valid(tokens, &shell))
		{
			free(line);
			free_tokens(&tokens);
			continue ;
		}
		print_l(&tokens);
		expand_tokens(tokens, shell.envp, &shell);
		cmd = parse_tokens(tokens);
		// printf("cmd validation = %d\n", cmd_validation(cmd));
		if (!cmd || cmd_validation(cmd))
		{
			free(line);
			free_tokens(&tokens);
			continue ;
		}
		print_cmd(cmd);
		free_cmd(cmd);
		cmd = NULL;
		free(line);
		free_tokens(&tokens);
	}
	free_env(shell.envp);
	rl_clear_history();
	return (0);
}
