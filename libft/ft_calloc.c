/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:35:24 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 17:05:20 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*ptr;
	size_t	count;

	ptr = NULL;
	count = 0;
	ptr = (char *)malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	while (count < (num * size))
	{
		ptr[count] = 0;
		count++;
	}
	return ((void *)ptr);
}
