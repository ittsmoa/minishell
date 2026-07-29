/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:17:55 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/29 02:40:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_append_variable(t_expand *expand)
{
	char	*key;
	char	*value;

	key = extract_var_name(expand->current + 1);
	if (!key)
		return (1);
	value = get_env_value(expand->shell->envp, key);
	expand->current += ft_strlen(key) + 1;
	free(key);
	return (expand_append_text(expand, value));
}

int	expand_append_status(t_expand *expand)
{
	char	*status;
	int		failed;

	status = ft_itoa(expand->shell->exit_status);
	if (!status)
		return (1);
	failed = expand_append_text(expand, status);
	free(status);
	if (failed)
		return (1);
	expand->current += 2;
	return (0);
}
