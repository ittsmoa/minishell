/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:30:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 02:40:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_split_delimiter(char value, char protected)
{
	return ((value == ' ' || value == '\t' || value == '\n')
		&& protected == '0');
}

static int	add_field(t_token **fields, char *value, size_t start, size_t len)
{
	t_token	*field;
	char	*text;

	text = ft_substr(value, start, len);
	if (!text)
		return (1);
	field = new_token(WORD, text);
	free(text);
	if (!field)
		return (1);
	field->expanded = 1;
	add_back(fields, field);
	return (0);
}

static void	attach_fields(t_token *token, t_token *fields)
{
	t_token	*last;
	t_token	*rest;

	rest = fields->next;
	free(token->value);
	token->value = fields->value;
	fields->value = NULL;
	free(fields);
	if (!rest)
		return ;
	last = rest;
	while (last->next)
		last = last->next;
	last->next = token->next;
	token->next = rest;
}

static int	collect_fields(t_token *token, char *mask, t_token **fields)
{
	size_t	start;
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		while (token->value[i]
			&& is_split_delimiter(token->value[i], mask[i]))
			i++;
		start = i;
		while (token->value[i]
			&& !is_split_delimiter(token->value[i], mask[i]))
			i++;
		if (i > start && add_field(fields, token->value, start, i - start))
			return (free_tokens(fields), -1);
		count += (i > start);
	}
	return (count);
}

int	split_expanded_word(t_token *token, char *mask)
{
	t_token	*fields;
	char	*empty;
	int		count;

	fields = NULL;
	count = collect_fields(token, mask, &fields);
	if (count == -1)
		return (1);
	token->ambiguous = (count != 1);
	if (!count && !token->quoted)
		return (token->skip = 1, 0);
	if (!count)
	{
		empty = ft_strdup("");
		if (!empty)
			return (1);
		free(token->value);
		token->value = empty;
		token->ambiguous = 0;
		return (0);
	}
	attach_fields(token, fields);
	return (0);
}
