/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 19:35:10 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/28 23:42:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_pipe(t_cmd **current)
{
	(*current)->next = new_cmd();
	if (!(*current)->next)
		return (1);
	*current = (*current)->next;
	return (0);
}

int	ft_is_redir(t_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND)
		return (1);
	return (0);
}

static int	valid_redir(t_token **tokens, t_cmd *current)
{
	t_token	*file;

	file = (*tokens)->next;
	if (!file || file->type != WORD || !file->value)
		return (1);
	if (add_redir(current, (*tokens)->type, file->value, file->quoted))
		return (1);
	*tokens = file;
	return (0);
}

static t_cmd	*parse_error(t_cmd *cmd)
{
	free_cmd(cmd);
	return (NULL);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current;

	cmd_list = new_cmd();
	if (!cmd_list)
		return (NULL);
	current = cmd_list;
	while (tokens)
	{
		if (tokens->type == WORD && !tokens->skip)
		{
			if (add_argv(current, tokens->value))
				return (parse_error(cmd_list));
		}
		else if (tokens->type == PIPE && handle_pipe(&current))
			return (parse_error(cmd_list));
		else if (ft_is_redir(tokens->type)
			&& valid_redir(&tokens, current))
			return (parse_error(cmd_list));
		tokens = tokens->next;
	}
	return (cmd_list);
}
