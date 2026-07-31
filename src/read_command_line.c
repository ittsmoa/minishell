/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmoa <xmoa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by xmoa              #+#    #+#             */
/*   Updated: 2026/07/31 00:00:00 by xmoa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*grow_line(char *line, size_t length, size_t *capacity)
{
	char	*grown;

	grown = malloc(*capacity * 2);
	if (!grown)
		return (free(line), NULL);
	ft_memcpy(grown, line, length);
	free(line);
	*capacity *= 2;
	return (grown);
}

static int	fill_line(char **line, size_t *length, size_t *capacity)
{
	ssize_t	count;
	char	current;

	count = read(STDIN_FILENO, &current, 1);
	while (count > 0 && current != '\n')
	{
		if (*length + 1 >= *capacity)
		{
			*line = grow_line(*line, *length, capacity);
			if (!*line)
				return (1);
		}
		(*line)[(*length)++] = current;
		count = read(STDIN_FILENO, &current, 1);
	}
	return (count < 0 || (count == 0 && *length == 0));
}

static char	*read_stdin_line(void)
{
	char	*line;
	size_t	length;
	size_t	capacity;

	capacity = 128;
	line = malloc(capacity);
	if (!line)
		return (NULL);
	length = 0;
	if (fill_line(&line, &length, &capacity))
		return (free(line), NULL);
	line[length] = '\0';
	return (line);
}

char	*read_command_line(char *prompt)
{
	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	return (read_stdin_line());
}
