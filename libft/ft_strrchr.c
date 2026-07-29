/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:39:06 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 16:37:57 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	count;
	int	indx;

	count = 0;
	indx = -1;
	while (s[count])
	{
		if (s[count] == (char)c)
		{
			indx = count;
		}
		count++;
	}
	if (c == '\0')
		return ((char *)(s + count));
	if (indx != -1)
		return ((char *)(s + indx));
	return (NULL);
}
//  int	main(void)
//  {
//  	char expl[] = "wello world";
//  	printf("%c\n", *ft_strrchr(expl, '\0'));
//  	return (0);
// }