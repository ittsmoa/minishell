/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 00:36:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/29 00:40:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*heredoc_temp_path(int index)
{
	char	*number;
	char	*path;

	number = ft_itoa(index);
	if (!number)
		return (NULL);
	path = ft_strjoin("/tmp/.minishell_heredoc_", number);
	free(number);
	return (path);
}

int	open_heredoc_file(int fds[2])
{
	char	*path;
	int		index;

	index = 0;
	while (index < 1000000)
	{
		path = heredoc_temp_path(index++);
		if (!path)
			return (1);
		fds[1] = open(path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fds[1] != -1)
		{
			fds[0] = open(path, O_RDONLY);
			unlink(path);
			free(path);
			if (fds[0] == -1)
				return (close(fds[1]), perror("heredoc"), 1);
			return (0);
		}
		if (errno != EEXIST)
			return (free(path), perror("heredoc"), 1);
		free(path);
	}
	return (1);
}

void	close_heredoc_fds(t_redir *redir)
{
	while (redir)
	{
		if (redir->heredoc_fd != -1)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}

void	print_heredoc_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted '", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

int	write_heredoc_line(int fd, char *line, t_redir *redir, t_shell *shell)
{
	char	*output;

	if (redir->delimiter_quoted)
		output = ft_strdup(line);
	else
		output = expand_heredoc_line(line, shell);
	if (!output)
		return (1);
	if (write(fd, output, ft_strlen(output)) == -1
		|| write(fd, "\n", 1) == -1)
	{
		free(output);
		return (1);
	}
	free(output);
	return (0);
}
