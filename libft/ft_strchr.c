/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 05:05:24 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 05:05:24 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
	{
		if ((unsigned char)s[count] == ((unsigned char)c))
			return ((char *)(s + count));
		count++;
	}
	if (c == '\0')
		return ((char *)(s + count));
	return (NULL);
}
