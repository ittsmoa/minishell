/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 12:42:59 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/19 06:01:24 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

int	parse_env(char *envp, char **key, char **value)
{
	char	*equal;

	if (!envp || !key || !value)
		return (0);
	equal = NULL;
	equal = ft_strchr(envp, '=');
	if (equal)
	{
		*key = ft_substr(envp, 0, equal - envp);
		*value = ft_strdup(equal + 1);
		if (!*key || !*value)
		{
			free(*key);
			free(*value);
			*key = NULL;
			*value = NULL;
			return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("KEY=[%s]\n", env->key);
		printf("VALUE=[%s]\n", env->value);
		printf("----------------\n");
		env = env->next;
	}
}

char	*get_value_of_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strlen(env->key) == ft_strlen(key)
			&& ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	expand_tokens(t_token *tokens, t_env *env, t_shell *shell)
{
	while (tokens)
	{
		if (tokens->type == WORD)
			expand_word(tokens, env, shell);
		tokens = tokens->next;
	}
}
