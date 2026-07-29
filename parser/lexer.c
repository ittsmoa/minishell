/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 06:30:04 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/18 20:10:00 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_type t, char *v)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->type = t;
	tmp->value = ft_strdup(v);
	if (!tmp->value)
	{
		free(tmp);
		return (NULL);
	}
	tmp->quoted = 0;
	tmp->skip = 0;
	tmp->ambiguous = 0;
	tmp->expanded = 0;
	tmp->next = NULL;
	return (tmp);
}

void	add_back(t_token **head, t_token *new_tok)
{
	t_token	*tmp;

	if (!head || !new_tok)
		return ;
	if (!(*head))
	{
		*head = new_tok;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_tok;
}

static char	*creat_word(char *w, size_t i, size_t j)
{
	char	*word;
	size_t	start;
	int		len;

	len = j - i;
	if (len < 0)
		return (NULL);
	start = 0;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (w[i] && i < j)
	{
		word[start] = w[i];
		i++;
		start++;
	}
	word[start] = '\0';
	return (word);
}

static int	handle_word(char *line, int i, t_token **head, char *token)
{
	int		j;
	char	qoute;

	j = i;
	while (line[j] && !ft_is_space(line[j]) && !ft_is_operation(line[j]))
	{
		if (line[j] == '\'' || line[j] == '"')
		{
			qoute = line[j++];
			while (line[j] && line[j] != qoute)
				j++;
			if (!line[j])
			{
				free_tokens(head);
				return (quote_error());
			}
			if (line[j] == qoute)
				j++;
		}
		else
			j++;
	}
	add_back(head, new_token(WORD, (token = creat_word(line, i, j))));
	free(token);
	return (j);
}

t_token	*lexer_line(char *line)
{
	int		i;
	t_token	*head;

	head = NULL;
	i = 0;
	while (line[i])
	{
		if (ft_is_space(line[i]))
			i++;
		else if (line[i] == '#')
			break ;
		else if (line[i] == '>')
			i = handle_redir_right(line, i, &head);
		else if (line[i] == '|')
			i += add_back_pipe(&head, new_token(PIPE, "|"));
		else if (line[i] == '<')
			i = handle_redir_left(line, i, &head);
		else
			i = handle_word(line, i, &head, NULL);
		if (i == -1)
			return (NULL);
	}
	return (head);
}
