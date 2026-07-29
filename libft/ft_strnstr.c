/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:38:55 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 01:30:23 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		while (i + j < len && big[i + j] == little[j] && little[j] != '\0')
		{
			j++;
		}
		if (little[j] == '\0')
		{
			return ((char *)(big + i));
		}
		i++;
		j = 0;
	}
	return (NULL);
}

// int	main(void)
// {
// 	int			count;
// 	const char	*s1 = "hezllo9 world";
// 	const char	*s2 = "llo9";

// 	count = 0;
// 	printf("%s", ft_strnstr(s1, s2, 0));
// 	return (0);
// }
