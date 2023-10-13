/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:06:31 by abasante          #+#    #+#             */
/*   Updated: 2023/10/13 16:59:28 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	theres_equal(char *args)
{
	int	equal;
	int	i;

	i = 0;
	equal = 0;
	while (args[i] && !equal)
	{
		if (args[i] == '=')
			equal = 1;
		i++;
	}
	return (equal);
}

int	export(t_env *env, char **args)
{
	t_env	*tmp;

	tmp = env;
	if (!args[1])
	{
		while (tmp != NULL)
		{
			ft_printf("declare -x %s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		if (theres_equal(args[1]))
			not_declare_x(env, args, tmp);
	}
	return (0);
}

int	not_declare_x(t_env *env, char **args, t_env *tmp)
{
	char	*var_name;
	char	*var_value;

	var_name = check_env_string(args);
	if (var_name == NULL)
		return (0);
	var_value = return_env_value(args);
	if (!give_variable(env, &tmp, var_name))
	{
		free(tmp->value);
		tmp->value = var_value;
		free(var_name);
	}
	else
	{
		tmp = ft_lstnew(var_name, var_value);
		ft_lstadd_back(env, tmp);
	}
	return (0);
}
