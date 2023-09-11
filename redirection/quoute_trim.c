/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoute_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larra <larra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:21:36 by larra             #+#    #+#             */
/*   Updated: 2023/09/08 20:14:27 by larra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "../expand/expand.h"

static int quoute_detector(char *s);

char	*q_t(char *s)
{
	int	start;
	int	end;

	start = 0;
	if (!quoute_detector(s))
		return (s);
	while (s[start] != '\"' && s[start] != '\'')
		start++;
	if (s[start] == '\'')
		end = start + find_quoute_end(&s[start]);
	if (s[start] == '\"')
		end = start + find_d_quoute_end(&s[start]);
	ft_printf("start: %d, end:%d\n", start, end);
	return (trim_quoutes(s, start, end));
	
}

static int quoute_detector(char *s)
{
	int	n;

	n = 0;
	while (s[n])
	{
		if (s[n] == '\"' || s[n] == '\'')
			return (1);
		n++;
	}
	return (0);
}

/*int	main(void)
{
	char	*s;
	char	*result;

	s = ft_strdup("inf\"ile\"1");
	result = q_t(s);
	ft_printf("s: %s\nresult: %s\n", s, result);
	//free(s);
	free(result);

}*/