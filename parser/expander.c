/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maradweh <maradweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:36:10 by maradweh          #+#    #+#             */
/*   Updated: 2026/07/19 11:46:14 by maradweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	replace_key_with_val(char **current, char **key,
		t_env	*env, char	**result)
{
	char	*tmp;
	char	*value;

	value = NULL;
	tmp = NULL;
	if (!*result || !*current || !*key || !env)
		return ;
	value = get_value_of_env(env, *key);
	if (value)
	{
		tmp = *result;
		*result = ft_strjoin(tmp, value);
		free(tmp);
	}
	*current += 1 + ft_strlen(*key);
	free(*key);
	*key = NULL;
}

static	void	appeand_char(char c, char **current, char **result)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	appeand_string(result, tmp);
	(*current)++;
}

static	void	expand_string(char	**result, char	**current,
		t_env	*env)
{
	char	*key;

	key = NULL;
	if (!(*current) || !(*result) || !env)
		return ;
	key = extract_var_name(((*current) + 1));
	if (key)
		replace_key_with_val(current, &key, env, result);
	else
		appeand_char(**current, current, result);
}

static	void	exp_word(char	**current, char	**result,
	t_env	*env, t_shell *shell)
{
	t_quote	quote;

	if (!(*current) || !(*result) || !env)
		return ;
	quote = UNQUOTED;
	while (**current)
	{
		if (quote_check(current, &quote))
			continue ;
		if (!**current)
			return ;
		else if (**current == '$' && quote != SINGEL && (*current)[1] == '?')
			appeand_exit_status(current, result, shell);
		else if (**current == '$' && ft_isalnum((*current)[1])
			&& quote != SINGEL)
			expand_string(result, current, env);
		else
			appeand_char(**current, current, result);
	}
}
/*add '_' to ft_isalnum*/

void	expand_word(t_token	*tokens, t_env	*env, t_shell *shell)
{
	char	*result;
	char	*current;

	result = ft_strdup("");
	current = tokens->value;
	if (!result)
		return ;
	exp_word(&current, &result, env, shell);
	free (tokens->value);
	tokens->value = result;
}
