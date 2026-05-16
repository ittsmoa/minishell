/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 13:01:28 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 13:01:28 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	add_env_value(char ***envp, char *new_var)
{
	char	**new_envp;
	int		i;

	if (!envp || !*envp || !new_var)
		return (1);
	new_envp = malloc(sizeof(char *) * (env_count(*envp) + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	if (!new_envp[i])
		return (free(new_envp), 1);
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
	return (0);
}