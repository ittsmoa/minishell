/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 11:54:26 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 11:54:26 by moatieh          ###   ########.fr       */
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

static char	*join_env(char *key, char *value)
{
	char	*tmp;
	char	*new_env;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	new_env = ft_strjoin(tmp, value);
	free(tmp);
	return (new_env);
}

int	set_env_value(char ***envp, char *key, char *value)
{
	int		i;
	int		len;
	char	*new_env;

	if (!envp || !*envp || !key || !value)
		return (1);
	i = 0;
	len = ft_strlen(key);
	while ((*envp)[i])
	{
		if (env_key_len((*envp)[i]) == len
			&& ft_strncmp((*envp)[i], key, len) == 0)
		{
			new_env = join_env(key, value);
			if (!new_env)
				return (1);
			free((*envp)[i]);
			(*envp)[i] = new_env;
			return (0);
		}
		i++;
	}
	return (1);
}