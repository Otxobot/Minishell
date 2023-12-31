/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:27:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/11/06 19:58:16 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../builtins/builtins.h"
#include "../redirection/redirection.h"
#include "../execution/execution.h"

/*This function calls all the other parsing functions in order. 
The input is modified by each one of them.

The first function checks for characters that we dont have to process.
As we dont need to process them we simply avoid them by
throwing an error of invalid character.
This way i think is harder to break our code.

The next two fucntions are splits, but the have some special conditions:
	- The first one splits by the spaces but without taking into 
	account the spaces that are between simple or double quoutes.
	- The second one spltis using the pipes, but instead of 
	making them dissapear puts them in a separated array.

After this 2 the expander is called. The expaders job is to substitute the
enviroment variables names that appear in the prompt for the value of 
each variable.

When the expansion is finished next step will be command creation,
quoute triming and then executing the commands.*/

int	prepare_execution(t_cmnd *head, t_env **env, char **envp);
int	execute_one(t_cmnd *node, t_env **env);

int	input_handle(char *input, t_env **env, char **envp)
{
	char	**args;
	t_cmnd	*head;

	if (check_valid(input))
		return (1);
	args = mini_split(input);
	args = pipe_spliter(args);
	args = expand(args, *env);
	head = cmnd_init();
	if (node_create(args, &head))
		return (free_cmnds(head), ft_double_free(args), 0);
	if (head->cmd == NULL)
		return (free_cmnds(head), ft_double_free(args), exit_status("set", 0));
	ft_double_free(args);
	if (before_execution(head, *env) != 0)
		return (free_cmnds(head), 3);
	prepare_execution(head, env, envp);
	free_cmnds(head);
	return (0);
}

int	prepare_execution(t_cmnd *head, t_env **env, char **envp)
{
	pid_t	pid;
	int		exit_s;
	int		status_code;
	int		command_count;
	t_cmnd	*tmp;

	command_count = 0;
	status_code = 0;
	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		command_count++;
	}
	if (!command_count && head->built_ptr)
		return (exit_status("set", execute_one(head, env)));
	pid = fork();
	if (pid == 0)
		fork_loop(&head, *env, envp);
	else
		waitpid(pid, &exit_s, 0);
	status_code = WEXITSTATUS(exit_s);
	if (command_count != 1 && g_signaled != 1)
		exit_status("set", status_code);
	return (0);
}

int	execute_one(t_cmnd *node, t_env **env)
{
	int					ret;
	int					fd[2];
	int					ev;

	ret = 0;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (node->redirs.o_r_type != 0)
		dup2(node->redirs.o_fd, STDOUT_FILENO);
	if (node->redirs.i_r_type != 0)
		dup2(node->redirs.i_fd, STDIN_FILENO);
	if (node->built_ptr == &exit_builtin)
	{
		ev = node->built_ptr(*env, node->cmd);
		if (ev == -358)
			return (1);
		free_cmnds(node);
		free_env(*env);
		exit(ev);
	}
	else
		ret = node->built_ptr(*env, node->cmd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	return (ret);
}
