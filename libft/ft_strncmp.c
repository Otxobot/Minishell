/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:57:29 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/06 15:16:05 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	m;
	size_t	j;

	m = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (*s2);
	if (!s2)
		return (*s1);
	if (n == 0)
		return (0);
	while (s1[j] && s2[m] && (unsigned char) s1[j] == (unsigned char) s2[m]
		&& m < n - 1)
	{
		j++;
		m++;
	}
	return (((unsigned char *)s1)[j] -((unsigned char *)s2)[m]);
}

/*int	main(void)
{
	const char	s1[] = "Hola que tal?";
	const char s2[] = "Hola qUe tAl?";

	printf("%d\n", ft_strncmp(s1, s2, 7));
}*/
