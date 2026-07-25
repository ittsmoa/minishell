/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:08:34 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/18 13:23:49 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_right(char *line, int i, t_token **head)
{
	if (line[i + 1] && line[i + 1] == '>')
	{
		add_back(head, new_token(APPEND, ">>"));
		return (i + 2);
	}
	else
	{
		add_back(head, new_token(REDIR_OUT, ">"));
		return (i + 1);
	}
}

int	handle_redir_left(char *line, int i, t_token **head)
{
	if (line[i + 1] == '<')
	{
		add_back(head, new_token(HEREDOC, "<<"));
		return (i + 2);
	}
	else
	{
		add_back(head, new_token(REDIR_IN, "<"));
		return (i + 1);
	}
}

int	has_ampersand(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '&')
			return (1);
		i++;
	}
	return (0);
}

int	quote_error(void)
{
	ft_putstr_fd("syntax error: unclosed quote\n", 2);
	return (-1);
}

int	add_back_pipe(t_token **head, t_token *new_token)
{
	add_back(head, new_token);
	return (1);
}
