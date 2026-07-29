/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:36:10 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/29 02:30:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_current(t_expand *expand)
{
	if (expand->current[0] == '$' && expand->current[1] == '?')
		return (expand_append_status(expand));
	if (expand->current[0] == '$' && (ft_isalnum(expand->current[1])
			|| expand->current[1] == '_'))
		return (expand_append_variable(expand));
	return (expand_append_char(expand));
}

static int	init_expand(t_expand *expand, t_token *token, t_shell *shell)
{
	expand->result = ft_strdup("");
	expand->mask = ft_strdup("");
	if (!expand->result || !expand->mask)
	{
		free(expand->result);
		free(expand->mask);
		return (1);
	}
	expand->current = token->value;
	expand->shell = shell;
	expand->token = token;
	expand->quote = UNQUOTED;
	return (0);
}

int	expand_word(t_token *token, t_shell *shell, int expand_variables)
{
	t_expand	expand;

	if (init_expand(&expand, token, shell))
		return (1);
	while (*expand.current)
	{
		if (quote_check(&expand.current, &expand.quote))
			token->quoted = 1;
		else if (expand_variables && expand.quote != SINGEL
			&& expand_current(&expand))
			return (free(expand.result), free(expand.mask), 1);
		else if ((!expand_variables || expand.quote == SINGEL)
			&& expand_append_char(&expand))
			return (free(expand.result), free(expand.mask), 1);
	}
	free(token->value);
	token->value = expand.result;
	token->expanded = 1;
	if (expand_variables && split_expanded_word(token, expand.mask))
		return (free(expand.mask), 1);
	free(expand.mask);
	return (0);
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	t_expand	expand;

	expand.result = ft_strdup("");
	if (!expand.result)
		return (NULL);
	expand.mask = NULL;
	expand.current = line;
	expand.shell = shell;
	expand.token = NULL;
	expand.quote = UNQUOTED;
	while (*expand.current)
	{
		if (expand_current(&expand))
			return (free(expand.result), NULL);
	}
	return (expand.result);
}
