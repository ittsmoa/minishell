/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_parser_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	temp_pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (1);
}

int	temp_parse_tokens(t_cmd *head, char **tokens)
{
	t_cmd	*tail;
	int		i;

	tail = head;
	i = 0;
	while (tokens[i])
	{
		if (temp_add_command_segment(head, &tail, tokens, i))
			return (1);
		while (tokens[i] && !temp_is_pipe(tokens[i]))
			i++;
		if (tokens[i] && temp_is_pipe(tokens[i]))
		{
			if (!tokens[i + 1])
				return (temp_pipe_error());
			i++;
		}
	}
	return (0);
}
