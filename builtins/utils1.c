/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:12:33 by abasante          #+#    #+#             */
/*   Updated: 2023/10/06 14:41:29 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*check_env_string(char **args)
{
	char	*var_name;
	int		i;
	int		a;

	i = 0;
	while (args[1][i] != '=')
	{
		if ((args[1][0] == '_' && args[1][1] == '=') || (ft_isdigit(args[1][0]) == 1))
		{
			ft_printf("export: '%s': not a valid identifier\n", args[1]);
			return (0);
		}
		i++;
	}
	a = i;
	while (args[1][i] && !ft_is_space(args[1][i]))
		i++;
	var_name = ft_substr(args[1], 0, a);
	return (var_name);
}

char	*return_env_value(char **args)
{
	char	*var_value;
	int		i;
	int		a;

	a = 0;
	i = 0;
	while (args[1][i] != '=')
		i++;
	i++;
	while (args[1][a] != '\0')
		a++;
	var_value = ft_substr(args[1], i, a);
	return (var_value);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

void	print_nodes(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd(tmp->name, 1);
		write (1, "=", 1);
		ft_putstr_fd(tmp->value, 1);
		write (1, "\n", 1);
		tmp = tmp->next;
	}
}

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
