/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:09:08 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 01:03:44 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a;
	size_t			count;

	a = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		*a = (unsigned char)c;
		a++;
		count++;
	}
	return (s);
}

// int	main(void)
// {
// 	char	p[] = "hello";
// 	char	*d;

// 	d = ft_memset(p, 'c', 0);
// 	printf("%s\n", d);
// }
