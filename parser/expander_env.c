/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:17:55 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/19 06:25:12 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_add_back(t_env **envp, t_env *new)
{
	t_env	*tmp;

	if (!envp || !new)
		return ;
	if (!*envp)
	{
		*envp = new;
		return ;
	}
	tmp = *envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static	t_env	*new_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (!node->value || !node->key)
	{
		free(node->value);
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static void	free_safe(char **key, char **value, int check, t_env *env_list)
{
	free(*key);
	free(*value);
	if (check == 1)
	{
		free_env(env_list);
	}
	else
		(void)env_list;
	*key = NULL;
	*value = NULL;
}

t_env	*read_env(char **envp)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*env_list;
	t_env	*node;

	env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		key = NULL;
		value = NULL;
		if (parse_env(envp[i], &key, &value))
		{
			node = new_env(key, value);
			if (!node)
			{
				free_safe(&key, &value, 1, env_list);
				return (NULL);
			}
			env_add_back(&env_list, node);
			free_safe(&key, &value, 0, env_list);
		}
	}
	return (env_list);
}

void	appeand_string(char **result, char *str)
{
	char	*tmp;

	if (!*result || !str)
		return ;
	tmp = *result;
	*result = ft_strjoin(tmp, str);
	free(tmp);
}
