/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 11:46:35 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 11:46:35 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_key_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

char	*get_env_value(char **envp, char *key)
{
	int	i;
	int	len;

	if (!envp || !key)
		return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (env_key_len(envp[i]) == len
			&& ft_strncmp(envp[i], key, len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}