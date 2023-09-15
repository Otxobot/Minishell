#include "execution.h"

t_builtin_function	check_if_builtin(t_cmnd **node)
{
	char	*string_in_node;
	int		pos;

	if (ft_strcmp((*node)->cmd[0], "unset") == 0)
		return (&unset);
	else if (ft_strcmp((*node)->cmd[0], "export") == 0)
		return (&export);
	else if (ft_strcmp((*node)->cmd[0], "exit") == 0)
		return (&exit_builtin);
	pos = slash_pos(node);
	string_in_node = ft_strdup(&(*node)->cmd[0][pos]);
	printf("string for builtin check: %s\n", string_in_node);
	if (ft_strcmp(string_in_node, "echo") == 0)
		return (free(string_in_node), &echo);
	else if (ft_strcmp(string_in_node, "cd") == 0)
		return (free(string_in_node), &cd);	
	else if (ft_strcmp(string_in_node, "env") == 0)
		return (free(string_in_node), &print_env);
	else if (ft_strcmp(string_in_node, "pwd") == 0)
		return (free(string_in_node), &pwd);
	else
		return (free(string_in_node), NULL);
}

int	slash_pos(t_cmnd **node)
{
	char	*slash;
	int		n;

	slash = (*node)->cmd[0];
	n = 0;
	while (slash)
	{
		slash = ft_strchr(&(*node)->cmd[0][n], '/');
		if (slash)
			n = slash - &((*node)->cmd[0][0]) + 1;
		printf("aaa\n");
		
	}
	return (n);
}
