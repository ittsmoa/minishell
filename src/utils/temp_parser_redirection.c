/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_parser_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_redirection_file(t_cmd *cmd, char *operator, char *file)
{
	int	fd;

	if (ft_strncmp(operator, "<", 2) == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (perror(file), 1);
		if (cmd->infile != -1)
			close(cmd->infile);
		cmd->infile = fd;
		return (0);
	}
	if (ft_strncmp(operator, ">>", 3) == 0)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(file), 1);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (0);
}

static void	remove_redirection_tokens(char **argv, int i)
{
	free(argv[i]);
	free(argv[i + 1]);
	while (argv[i + 2])
	{
		argv[i] = argv[i + 2];
		i++;
	}
	argv[i] = NULL;
	argv[i + 1] = NULL;
}

int	temp_is_redirection(char *arg)
{
	return (ft_strncmp(arg, ">", 2) == 0
		|| ft_strncmp(arg, ">>", 3) == 0
		|| ft_strncmp(arg, "<", 2) == 0);
}

static int	handle_redirection(t_cmd *cmd, int i)
{
	if (!cmd->argv[i + 1])
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("`newline'\n", 2);
		return (1);
	}
	if (temp_is_redirection(cmd->argv[i + 1]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(cmd->argv[i + 1], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	if (open_redirection_file(cmd, cmd->argv[i], cmd->argv[i + 1]))
		return (1);
	remove_redirection_tokens(cmd->argv, i);
	return (0);
}

int	temp_parse_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (temp_is_redirection(cmd->argv[i]))
		{
			if (handle_redirection(cmd, i))
				return (1);
			i = 0;
			continue ;
		}
		i++;
	}
	return (0);
}
