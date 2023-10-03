/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:16:02 by abasante          #+#    #+#             */
/*   Updated: 2023/10/02 19:27:06 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFFER_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*search_for_var(t_env *env, char *search)
{
	t_env	*tmp;
	char	*ret_path;

	ret_path = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, search) == 0)
		{
			ret_path = tmp->value;
		}
		tmp = tmp->next;
	}
	return (ret_path);
}

int	give_variable(t_env *env, t_env **ret, char *search)
{
	*ret = env;
	while ((*ret) != NULL)
	{
		if (ft_strcmp((*ret)->name, search) == 0)
			return (0);
		*ret = (*ret)->next;
	}
	return (1);
}
