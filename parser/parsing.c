/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 19:35:10 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/19 20:49:38 by maradweh         ###   ########.fr       */
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
	if (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == HEREDOC
		|| type == APPEND)
		return (1);
	return (0);
}

static	int	valid_redir(t_token **tokens, t_cmd *current)
{
	if (!(*tokens)->next
		|| (*tokens)->next->type != WORD
		|| !(*tokens)->next->value)
		return (1);
	if (add_redir(current, (*tokens)->type, (*tokens)->next->value))
		return (1);
	*tokens = (*tokens)->next;
	return (0);
}

static	t_cmd	*clean_free(char *p)
{
	free(p);
	return (NULL);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current;
	char	*tmp;

	cmd_list = new_cmd();
	if (!cmd_list)
		return (NULL);
	current = cmd_list;
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			tmp = remove_quotes(tokens->value);
			if (!tmp || add_argv(current, tmp))
				return (clean_free(tmp));
			free(tmp);
		}
		else if (tokens->type == PIPE && handle_pipe(&current))
			return (NULL);
		else if (ft_is_redir(tokens->type))
			if (valid_redir(&tokens, current))
				return (NULL);
		tokens = tokens->next;
	}
	return (cmd_list);
}
