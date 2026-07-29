/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utilities2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 07:41:36 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/29 00:09:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char *str)
{
	char	*start;
	size_t	len;

	if (!str)
		return (NULL);
	start = str;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	len = str - start;
	if (len == 0)
		return (NULL);
	return (ft_substr(start, 0, len));
}

t_quote	quote_states(char **current, t_quote quote)
{
	if (**current == '\'' && quote != DOUBLE)
	{
		if (quote == SINGEL)
			quote = UNQUOTED;
		else
			quote = SINGEL;
	}
	else if (**current == '"' && quote != SINGEL)
	{
		if (quote == DOUBLE)
			quote = UNQUOTED;
		else
			quote = DOUBLE;
	}
	(*current)++;
	return (quote);
}

int	quote_check(char **current, t_quote *quote)
{
	if ((**current == '\'' && *quote != DOUBLE)
		|| (**current == '"' && *quote != SINGEL))
	{
		*quote = quote_states(current, *quote);
		return (1);
	}
	return (0);
}
