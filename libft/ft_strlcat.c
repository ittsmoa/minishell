/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:37:55 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 16:39:09 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dcount;
	size_t		count;
	size_t		srclen;
	size_t		temp;

	srclen = 0;
	dcount = 0;
	count = 0;
	temp = 0;
	while (dst[dcount] != '\0' && dcount < size)
		dcount++;
	temp = dcount;
	while (src[srclen] != '\0')
		srclen++;
	if (dcount >= size)
		return (srclen + size);
	while (src[count] != '\0' && (dcount + count + 1) < size)
	{
		dst[dcount + count] = src[count];
		count++;
	}
	dst[dcount + count] = '\0';
	return (temp + srclen);
}

// int	main(void)
// {
// 	char	dst[50] = "hi i mohammed";
// 	char	src[50] = "hello";
// 	int		size;
// 	size_t	test;

// 	size = 32;
// 	test = ft_strlcat(dst, src, size);
// 	printf("%ld\n",ft_strlcat(dst, src, size));
// 	printf("%s\n", dst);
// 	printf("%ld\n", strlcat(dst, src, size));
// }
