/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:08:34 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/31 10:11:56 by maradweh         ###   ########.fr       */
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
	add_back(head, new_token(REDIR_OUT, ">"));
	return (i + 1);
}

int	handle_redir_left(char *line, int i, t_token **head)
{
	if (line[i + 1] == '<')
	{
		add_back(head, new_token(HEREDOC, "<<"));
		return (i + 2);
	}
	add_back(head, new_token(REDIR_IN, "<"));
	return (i + 1);
}

int	has_ampersand(char *s)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else if (!quote && s[i] == '&')
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
