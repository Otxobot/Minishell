#include "builtins.h"

t_env	*search_for_name_to_unset(t_env *env, char *search)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, search) == 0)
			return(tmp);
		tmp = tmp->next;
	}
	return 0;
}

void	remove_var_from_env(t_temp *func, t_env *to_unset, t_env *env)
{
	while (func->two != to_unset)
	{
		func->one = func->one->next;
		func->two = func->two->next;
	}
	func->one = func->two->next;
}
