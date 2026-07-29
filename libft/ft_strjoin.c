/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:37:44 by moatieh           #+#    #+#             */
/*   Updated: 2025/08/30 03:13:49 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cpy(char *str, char const *first, char const *sec)
{
	int		i;
	int		j;

	i = 0;
	while (first[i])
	{
		str[i] = first[i];
		i++;
	}
	j = 0;
	while (sec[j])
	{
		str[i + j] = sec[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	total;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	total = 0;
	while (s1[total])
		total++;
	while (s2[i])
		i++;
	total += i;
	str = (char *)malloc((total + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = cpy(str, s1, s2);
	return (str);
}

//   int	main(void)
//   {
//   	char s1[] = "hello";
//   	char s2[] = " world";
//   	printf("%s", ft_strjoin(s1, s2));
//   }