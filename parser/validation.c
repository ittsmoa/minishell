/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:17:51 by maradweh          #+#    #+#             */
/*   Updated: 2026/08/01 15:37:41 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND)
		return (1);
	return (0);
}

static int	validate_operators(t_token *tmp, t_shell *shell)
{
	if (tmp->type == PIPE)
	{
		if (!tmp->next)
			return (error_msg("invalid pipe", shell));
		if (tmp->next->type == PIPE)
			return (error_msg("|", shell));
	}
	else if (tmp->value && ft_strncmp(tmp->value, "&&", 3) == 0)
		return (error_msg("&&", shell));
	else if (tmp->value && ft_strncmp(tmp->value, "&", 2) == 0)
		return (error_msg("&", shell));
	else if (tmp->value && has_ampersand(tmp->value))
		return (error_msg("&", shell));
	return (1);
}

int	ft_is_valid(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;

	if (!tokens)
		return (0);
	tmp = tokens;
	if (tmp->type == PIPE)
		return (error_msg("Invalid Starting with |", shell));
	while (tmp)
	{
		if (is_redir(tmp->type))
		{
			if (!tmp->next)
				return (error_msg(tmp->value, shell));
			if (tmp->next->type != WORD)
				return (error_msg(tmp->next->value, shell));
		}
		else if (validate_operators(tmp, shell) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	validation_redir(t_shell	*shell, t_cmd	*cmd)
{
	t_cmd	*current;
	t_redir	*redir;

	if (!shell || !cmd)
		return (0);
	current = cmd;
	while (current)
	{
		redir = current->redirs;
		while (redir)
		{
			if (is_redir(redir->type) && !redir->file)
				return (error_msg("missing filename", shell));
			redir = redir->next;
		}
		current = current->next;
	}
	return (1);
}
