/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipeline(t_shell *shell, t_pipeline *pipeline, int count)
{
	pipeline->pids = malloc(sizeof(pid_t) * count);
	if (!pipeline->pids)
	{
		shell->exit_status = 1;
		return (1);
	}
	pipeline->prev_fd = -1;
	pipeline->started = 0;
	return (0);
}

int	wait_pipeline(t_pipeline *pipeline)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 1;
	while (i < pipeline->started)
	{
		if (waitpid(pipeline->pids[i], &status, 0) != -1
			&& i == pipeline->started - 1)
			last_status = get_process_status(status);
		i++;
	}
	return (last_status);
}
