/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:04:32 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/22 11:38:59 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->heredoc_fd != -1)
			close(redir->heredoc_fd);
		wait_heredoc_writer(redir->heredoc_pid);
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		close_command_fds(cmd);
		free_argv(cmd->argv);
		free_redir(cmd->redirs);
		free(cmd);
		cmd = tmp;
	}
}

char	*remove_quotes(char *argv)
{
	int		i;
	int		j;
	char	*new;
	char	qoute;

	j = 0;
	i = 0;
	qoute = 0;
	if (!argv)
		return (NULL);
	new = malloc(ft_strlen(argv) + 1);
	if (!new)
		return (NULL);
	while (argv[i])
	{
		if (!qoute && (argv[i] == '"' || argv[i] == '\''))
			qoute = argv[i];
		else if (qoute && argv[i] == qoute)
			qoute = 0;
		else
			new[j++] = argv[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	if (!arg || !(*arg))
		return (0);
	while (arg[i])
		i++;
	return (i);
}
