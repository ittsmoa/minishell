/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_parser_segment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	temp_is_pipe(char *arg)
{
	return (ft_strncmp(arg, "|", 2) == 0);
}

static int	count_segment_args(char **tokens, int start)
{
	int	count;

	count = 0;
	while (tokens[start + count] && !temp_is_pipe(tokens[start + count]))
		count++;
	return (count);
}

static char	**copy_segment_argv(char **tokens, int start, int count)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		argv[i] = ft_strdup(tokens[start + i]);
		if (!argv[i])
			return (free_split(argv, i), NULL);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static t_cmd	*next_cmd_slot(t_cmd *head, t_cmd **tail)
{
	t_cmd	*new_cmd;

	if (!head->argv)
	{
		*tail = head;
		return (head);
	}
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	temp_init_cmd(new_cmd);
	(*tail)->next = new_cmd;
	*tail = new_cmd;
	return (new_cmd);
}

int	temp_add_command_segment(t_cmd *head, t_cmd **tail,
		char **tokens, int start)
{
	t_cmd	*cmd;
	int		count;

	count = count_segment_args(tokens, start);
	if (count == 0)
		return (temp_pipe_error());
	cmd = next_cmd_slot(head, tail);
	if (!cmd)
		return (1);
	cmd->argv = copy_segment_argv(tokens, start, count);
	if (!cmd->argv)
		return (1);
	if (temp_parse_redirections(cmd))
		return (1);
	if (!cmd->argv[0])
		return (ft_putstr_fd("minishell: empty command\n", 2), 1);
	return (0);
}
