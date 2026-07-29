/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:37:19 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 17:15:08 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	slen;
	int		count;

	slen = ft_strlen(s);
	cpy = (char *)malloc((slen + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	count = 0;
	while (s[count])
	{
		cpy[count] = s[count];
		count++;
	}
	cpy[count] = '\0';
	return (cpy);
}

// int	main(void)
// {
// 	char *s = "hi i am moa";
// 	char *copy = ft_strdup(s);

// 	printf("Original: %s\nCopy    : %s\n", s, copy);
// 	free(copy);
// }