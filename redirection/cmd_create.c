/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:15:33 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/05 16:22:22 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../expand/expand.h"
#include <fcntl.h>

int	redirection_case(char **spltd, int *n, int *m, t_cmnd **tmp);
int	get_i_redir(char **spltd, int *n, int *m, t_cmnd **tmp);
int	get_o_redir(char **spltd, int *n, int *m, t_cmnd **tmp);

	//*head = cmnd_init();
	//tmp = *head;
/*This function takes the input array after expanding. It takes commands, 
and takes the redirections that should be done.*/

int	cmd_create(char **spltd, t_cmnd **head)
{
	int		n;
	int		m;    
	t_cmnd  *tmp;
	
	n = -1;
	*head = cmnd_init();
	tmp = *head;
	while (spltd[++n])
	{
		m = -1;
		ft_printf("analizing string %d: %s\n", n, spltd[n]);
		while (spltd[n][++m])
		{
			if (spltd[n][m] == '<' || spltd[n][m] == '>')
				if (redirection_case(spltd, &n, &m, &tmp))
					return (1);
			else if (spltd[n][m] == '|')
				if (pipe_case(&tmp))
					return(2);
			else
				if(add_cmnd(spltd[n], &m, tmp))
					return (3);
		}
	}
	return(0);
}

int	redirection_case(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	if (spltd[*n][*m] == '<')
	{
		if ((*tmp)->redirs.i_r_type)
			close_previous_in(&(*tmp));
		if (spltd[*n][*m + 1] == '<')
			(*tmp)->redirs.i_r_type = 2;
		else
			(*tmp)->redirs.i_r_type = 1;
		if (get_i_redir(spltd, n, m, &(*tmp)))
			return(1);
	}
	else
	{
		if ((*tmp)->redirs.o_r_type)
			close((*tmp)->redirs.o_fd);
		if (spltd[*n][*m + 1] == '>')
			(*tmp)->redirs.o_r_type = 2;
		else
			(*tmp)->redirs.o_r_type = 1;
		if (get_o_redir(spltd, n, m, &(*tmp)))
			return(1);
	}
	return(0);
}

int	get_i_redir(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	char *holder;

	while (spltd[*n][*m] == '<')
		*m += 1;
	if (spltd[*n][*m] == '\0')
	{
		*n += 1;
		*m = 0; 
	}
	if (spltd[*n][*m] == '\"' || spltd[*n][*m] == '\'')
		*m += 1;
	holder = ft_substr(&spltd[*n][*m], 0, find_end_word(spltd, *n, *m));
	if (ft_strlen(holder) == 0)
		return (redir_error(spltd[*n][*m]), free(holder), 1);
	else if ((*tmp)->redirs.i_r_type == 1)
	{
		(*tmp)->redirs.i_fd = open(holder, O_RDONLY);
		if ((*tmp)->redirs.i_fd == -1)
			return (1);
	}
	else if ((*tmp)->redirs.i_r_type == 2)
		(*tmp)->redirs.h_lim =  holder;  //this needs dup?.
	return (*m += ft_strlen(holder), free(holder), 0);
}

int	get_o_redir(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	char *holder;

	while (spltd[*n][*m] == '>')
		*m += 1;
	if (spltd[*n][*m] == '\0')
	{
		*n += 1;
		*m = 0; 
	}
	if (spltd[*n][*m] == '\"' || spltd[*n][*m] == '\'')
		*m += 1;
	holder = ft_substr(&spltd[*n][*m], 0, find_end_word(spltd, *n, *m));
	if (ft_strlen(holder) == 0)
		return(redir_error(spltd[*n][*m]), (holder), 1);
	else if ((*tmp)->redirs.i_r_type == 1)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT| O_TRUNC);
	else if ((*tmp)->redirs.i_r_type == 2)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT | O_APPEND);
	printf("fd name or limit is: %s\n", holder);
	return(free(holder), (*tmp)->redirs.o_fd == -1);
}

int pipe_case(t_cmnd **tmp)
{
	int		fd[2];
	t_cmnd	*new;

	if (pipe(fd) == -1)
		return (1);
	new = cmnd_init();
	(*tmp)->next = new;
	if ((*tmp)->redirs.o_r_type == 0)
	{
		(*tmp)->redirs.o_fd = fd[0];
		(*tmp)->redirs.o_r_type = 3;
	}
	*tmp = (*tmp)->next;
	(*tmp)->redirs.i_r_type = 3;
	(*tmp)->redirs.i_fd = fd[1];
	return (0);
}

int	main(void)
{
	char	**str;
	t_cmnd	*cmds;

	cmds = NULL;
	str = malloc(5 * sizeof(char *));
	str[4] = NULL;
	str[0] = ft_strdup("echo>>infile");
	str[1] = ft_strdup("|");
	str[2] = ft_strdup("cat<\"infile3\"");
	str[3] = ft_strdup("cat<'infile4'");
	if (cmd_create(str, cmds))
		ft_printf("FAILED WHILE OPENING FDS\n");
	ft_print_cmnds(cmds);
	ft_double_free(str);
}