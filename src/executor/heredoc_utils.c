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

static int	grow_heredoc_buffer(t_heredoc_buffer *buffer, size_t needed)
{
	char	*data;
	size_t	capacity;

	if (buffer->capacity >= needed)
		return (0);
	capacity = buffer->capacity;
	if (capacity == 0)
		capacity = 4096;
	while (capacity < needed)
		capacity *= 2;
	data = malloc(capacity);
	if (!data)
		return (1);
	if (buffer->data)
	{
		ft_memcpy(data, buffer->data, buffer->length);
		free(buffer->data);
	}
	buffer->data = data;
	buffer->capacity = capacity;
	return (0);
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

int	append_heredoc_line(t_heredoc_buffer *buffer, char *line,
		t_redir *redir, t_shell *shell)
{
	char	*output;
	size_t	length;

	if (redir->delimiter_quoted)
		output = ft_strdup(line);
	else
		output = expand_heredoc_line(line, shell);
	if (!output)
		return (1);
	length = ft_strlen(output);
	if (grow_heredoc_buffer(buffer, buffer->length + length + 2))
		return (free(output), 1);
	ft_memcpy(buffer->data + buffer->length, output, length);
	buffer->length += length;
	buffer->data[buffer->length++] = '\n';
	buffer->data[buffer->length] = '\0';
	free(output);
	return (0);
}

int	write_heredoc_buffer(int fd, t_heredoc_buffer *buffer)
{
	ssize_t	result;
	size_t	written;

	written = 0;
	while (written < buffer->length)
	{
		result = write(fd, buffer->data + written,
				buffer->length - written);
		if (result == -1 && errno == EINTR)
			continue ;
		if (result <= 0)
			return (1);
		written += result;
	}
	return (0);
}
