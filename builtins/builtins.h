/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:51:21 by abasante          #+#    #+#             */
/*   Updated: 2023/10/06 14:09:32 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define ERROR 1
# define SUCCESS 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_temp
{
	t_env	*one;
	t_env	*two;
}				t_temp;

typedef struct s_ex
{
	int		exit;
	int		ret;
}				t_ex;

				//BUILTIN FUNCTIONS:
int		cd(t_env *env, char **args);
int		echo(t_env *env, char **args);
int		pwd(t_env *env, char **cmd);
int		export(t_env *env, char **args);
int		exit_builtin(t_env *env, char **cmd);
int		print_env(t_env *env, char **standardized);

				//FUNCTIONS:
t_env	*get_env(char **envp, t_env *env);
char	*get_env_name(char *dest, const char *src);
t_env	*make_node(void);
void	print_nodes(t_env *env);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env *lst, t_env *new);
int		ft_strcmp(char *s1, char *s2);
char	*search_for_var(t_env *env, char *search);
int		home_case(t_env *env);
int		slash_case(t_env *env);
int		go_back(t_env *env);
int		absolute_path(t_env *env, char *absolute_path);
int		do_whatever(void);
int		check_var_name(char arg);
int		give_variable(t_env *env, t_env **tmp, char *search);
t_env	*ft_lstnew(char	*name, char *value);
char	*return_env_value(char **args);
int		ft_strisnum(const char *str);
int		ft_isalpha(int c);

				//EXPORT:
char	*check_env_string(char **args);
int		not_declare_x(t_env *env, char **args, t_env *tmp);

				//CD:
int		update_oldpwd(t_env *env, char *oldpwd);
int		update_pwd(t_env *env, char *pwd);

				//UNSET:
int		unset(t_env *env, char **args);
t_env	*search_for_name_to_unset(t_env *env, char *search);
void	remove_var_from_env(t_env *to_unset, t_env *env, t_temp *func);

#endif
