/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 12:42:59 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/29 02:40:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_mask(t_expand *expand, char *text)
{
	char	*new_mask;
	size_t	old_len;
	size_t	text_len;

	old_len = ft_strlen(expand->mask);
	text_len = ft_strlen(text);
	new_mask = malloc(old_len + text_len + 1);
	if (!new_mask)
		return (NULL);
	ft_memcpy(new_mask, expand->mask, old_len);
	ft_memset(new_mask + old_len, '0'
		+ (expand->quote != UNQUOTED), text_len);
	new_mask[old_len + text_len] = '\0';
	return (new_mask);
}

int	expand_append_text(t_expand *expand, char *text)
{
	char	*joined;
	char	*new_mask;

	if (!text)
		return (0);
	joined = ft_strjoin(expand->result, text);
	if (!joined)
		return (1);
	new_mask = NULL;
	if (expand->token)
	{
		new_mask = build_mask(expand, text);
		if (!new_mask)
			return (free(joined), 1);
	}
	free(expand->result);
	free(expand->mask);
	expand->result = joined;
	expand->mask = new_mask;
	return (0);
}

int	expand_append_char(t_expand *expand)
{
	char	text[2];

	text[0] = *expand->current;
	text[1] = '\0';
	expand->current++;
	return (expand_append_text(expand, text));
}

static int	ambiguous_redirect(t_token *token, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	if (token->value[0])
	{
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd("ambiguous redirect\n", 2);
	shell->exit_status = 1;
	return (1);
}

int	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*previous;
	int		expand_variables;

	previous = NULL;
	while (tokens)
	{
		if (tokens->type == WORD && !tokens->expanded)
		{
			expand_variables = (!previous || previous->type != HEREDOC);
			if (expand_word(tokens, shell, expand_variables))
				return (shell->exit_status = 1, 1);
			if (previous && ft_is_redir(previous->type)
				&& previous->type != HEREDOC
				&& (tokens->skip || tokens->ambiguous))
				return (ambiguous_redirect(tokens, shell));
		}
		previous = tokens;
		tokens = tokens->next;
	}
	return (0);
}
