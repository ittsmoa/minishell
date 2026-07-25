/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 19:36:39 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/19 20:45:49 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_argv(t_cmd *current, char *word)
{
	char	**new_argv;
	int		size;
	int		i;

	if (!current || !word)
		return (1);
	i = -1;
	new_argv = NULL;
	size = count_arg(current->argv);
	new_argv = malloc(sizeof(char *) * (size + 2));
	if (!new_argv)
		return (1);
	while (++i < size)
		new_argv[i] = current->argv[i];
	new_argv[i] = ft_strdup(word);
	if (!new_argv[i])
	{
		free(new_argv);
		return (1);
	}
	new_argv[i + 1] = NULL;
	free(current->argv);
	current->argv = new_argv;
	return (0);
}

void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	if (!head || !new)
		return ;
	tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_redir	*new_redir(t_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

int	add_redir(t_cmd *current, t_type type, char *file)
{
	t_redir	*redir;

	if (!current || !file || file[0] == '\0')
		return (1);
	if (!ft_is_redir(type))
		return (1);
	redir = new_redir(type, file);
	if (!redir)
		return (1);
	redir_add_back(&current->redirs, redir);
	return (0);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}
