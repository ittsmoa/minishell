/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	int		is_head;

	if (!cmd)
		return ;
	current = cmd;
	is_head = 1;
	while (current)
	{
		next = current->next;
		close_command_fds(current);
		if (current->argv)
			free_split(current->argv, -1);
		if (!is_head)
			free(current);
		is_head = 0;
		current = next;
	}
	cmd->argv = NULL;
	cmd->next = NULL;
}

void	temp_init_cmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->next = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
}

t_cmd	temp_parse_line(char *line)
{
	t_cmd	cmd;
	char	**tokens;

	temp_init_cmd(&cmd);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (cmd);
	if (temp_parse_tokens(&cmd, tokens))
	{
		free_cmd(&cmd);
		cmd.argv = NULL;
	}
	free_split(tokens, -1);
	return (cmd);
}
