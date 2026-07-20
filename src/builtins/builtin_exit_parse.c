/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_is_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static unsigned long long	get_exit_limit(char *arg, int *i, int *sign)
{
	*sign = 1;
	*i = 0;
	if (arg[*i] == '+' || arg[*i] == '-')
	{
		if (arg[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (*sign == -1)
		return (9223372036854775808ULL);
	return (9223372036854775807ULL);
}

int	parse_exit_value(char *arg, int *status)
{
	unsigned long long	value;
	unsigned long long	limit;
	int					sign;
	int					i;

	value = 0;
	limit = get_exit_limit(arg, &i, &sign);
	while (arg[i])
	{
		if (value > (limit - (arg[i] - '0')) / 10)
			return (1);
		value = value * 10 + (arg[i] - '0');
		i++;
	}
	if (sign == -1)
		*status = (unsigned char)(0 - (value % 256));
	else
		*status = (unsigned char)(value % 256);
	return (0);
}
