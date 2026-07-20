/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by moatieh           #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	text_compare(char *a, char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return ((unsigned char)*a - (unsigned char)*b);
}

static void	sort_entries(char **entries, int count)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (text_compare(entries[j], entries[j + 1]) > 0)
			{
				tmp = entries[j];
				entries[j] = entries[j + 1];
				entries[j + 1] = tmp;
			}
		}
	}
}

static void	print_export_entry(char *entry)
{
	char	*equal;

	equal = ft_strchr(entry, '=');
	ft_putstr_fd("declare -x ", 1);
	if (!equal)
		return (ft_putendl_fd(entry, 1));
	write(1, entry, equal - entry + 1);
	ft_putchar_fd('"', 1);
	equal++;
	while (*equal)
	{
		if (*equal == '"' || *equal == '\\' || *equal == '$'
			|| *equal == '`')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(*equal++, 1);
	}
	ft_putstr_fd("\"\n", 1);
}

int	print_export(t_shell *shell)
{
	char	**entries;
	int		count;
	int		i;

	count = 0;
	while (shell->envp[count])
		count++;
	entries = malloc(sizeof(char *) * count);
	if (!entries && count)
		return (1);
	i = -1;
	while (++i < count)
		entries[i] = shell->envp[i];
	sort_entries(entries, count);
	i = -1;
	while (++i < count)
		print_export_entry(entries[i]);
	free(entries);
	return (0);
}
