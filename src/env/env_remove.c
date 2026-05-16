/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:55:48 by moatieh           #+#    #+#             */
/*   Updated: 2026/05/16 15:55:48 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int evn_count(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    return (i);
}

static  int env_key_match(char *env, char *key)
{
    int len;

    len = ft_strlen(key);
    if (ft_strncmp(env, key, len) == 0 && env[len] == '=')
        return 1;
    return 0;
}

int remove_env_value(char ***envp, char *key)
{
    char    **new_envp;
    int i;
    int j;

    if (!envp || !*envp || !key)
        return 1;
    new_envp = malloc(sizeof(char *) * evn_count(*envp));
    if (!new_envp)
        return 1;
    i = 0;
    j = 0;
    while ((*envp)[i])
    {
        if (env_key_match((*envp)[i], key))
            free((*envp)[i]);
        else
            new_envp[j++] = (*envp)[i];
        i++;
    }
    new_envp[j] = NULL;
    free(*envp);
    *envp = new_envp;
    return 0;
}
