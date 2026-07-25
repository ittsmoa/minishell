/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utilities2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 07:41:36 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/19 11:45:52 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char	*str)
{
	char	*start;
	size_t	len;
	char	*key;

	if (!str)
		return (NULL);
	key = NULL;
	start = str;
	while ((ft_isalnum(*str) || *str == '_'))
		str++;
	len = str - start;
	if (len == 0)
		return (NULL);
	key = ft_substr(start, 0, len);
	return (key);
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

void	appeand_exit_status(char **current, char **result, t_shell *shell)
{
	char	*tmp;
	char	*exit_code_str;

	if (!current || !result
		|| !shell || !*current || !*result)
	{
		return ;
	}
	exit_code_str = ft_itoa(shell->exit_status);
	tmp = malloc(sizeof(char) * ft_strlen(*current));
	if (!tmp)
		return ;
	tmp = *result;
	*result = ft_strjoin(tmp, exit_code_str);
	if (!result || !*result)
	{
		free(tmp);
		return ;
	}
	free (tmp);
	free (exit_code_str);
	*current += 2;
}

int	quote_check(char	**current, t_quote	*quote)
{
	if (**current == '\'' || **current == '"')
	{
		*quote = quote_states(current, *quote);
		return (1);
	}
	return (0);
}
