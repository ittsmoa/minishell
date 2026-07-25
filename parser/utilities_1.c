/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 01:10:47 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/22 12:29:49 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_l(t_token **head)
{
	t_token	*tmp;

	if (!head || !(*head))
		return ;
	tmp = *head;
	while (tmp)
	{
		printf("[%d : %s] \n ", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_is_operation(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	error_msg(char *token, t_shell	*shell)
{
	shell->exit_status = 2;
	write(2, "ERROR: '", 8);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	return (0);
}
