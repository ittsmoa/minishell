/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:01:06 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 16:53:41 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			count;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	count = 0;
	while (count < n)
	{
		if (str1[count] != str2[count])
		{
			return ((unsigned char)str1[count] - (unsigned char)str2[count]);
		}
		count++;
	}
	return (0);
}
/*
int	main(void)
{
	int count = 0;
	const char *s1 = "hezllo world";
	const char *s2 = "hzello world";
	printf("%d", ft_memcmp(s1, s2, 10));

	return (0);
}*/