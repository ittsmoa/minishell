/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 19:41:39 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/16 00:43:49 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd)
	{
		return ;
	}
	while (cmd)
	{
		printf("===== CMD %d =====\n", i);
		printf("ARGV:\n");
		print_argv(cmd->argv);
		printf("REDIRS:\n");
		print_redir(cmd->redirs);
		cmd = cmd->next;
		i++;
	}
}

void	print_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
}

char	*redir_name(t_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == APPEND)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	return ("UNKNOWN");
}

void	print_redir(t_redir *redir)
{
	while (redir)
	{
		printf("redirection : %s\n %s\n", redir_name(redir->type), redir->file);
		redir = redir->next;
	}
}
