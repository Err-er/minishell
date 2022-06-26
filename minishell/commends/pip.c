/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:22:23 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/26 13:19:29 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_ex_com_pipe(t_vars *var, t_cd *cd, t_list *node)
{
	if (ft_check_pip2(node, INPUT_H) && var-> value)
	{
		if (pipe(var->end) == -1)
			perror("Error");
		ft_putstr_fd(var->value, var->end[1]);
		close(var->end[1]);
		dup2(var->end[0], 0);
		close(var->end[0]);
	}
	var->id[var->i] = forkpipe(var->end);
	if (var->id[var->i] == -1)
		exit(127);
	if (var->id[var->i] == 0)
	{
		var->node = node;
		if (!var->str[var->i + 1])
			var->c2 = 1;
		if (var->i == 0)
			ft_child1(var->str[var->i], cd, var->end, var);
		else if (ft_cheak(var->i, var->str) == 2)
			ft_child2(var->str[var->i], cd, var);
		else if (ft_cheak(var->i, var->str) == 3)
			ft_child3(var->str[var->i], cd, var->end, var);
	}
}

int	ft_wait_p(t_vars *var)
{
	int	j;
	int	ex;

	j = -1;
	while (++j < var->i)
		waitpid(var->id[j], &ex, 0);
	return (ex);
}

void	ft_dup_p(t_vars *var)
{
	if (var->br)
	{
		if (pipe(var->end) == -1)
			perror("Error");
	}
	if (var->str[var->i + 1])
	{
		dup2(var->end[0], 0);
		close(var->end[0]);
		close(var->end[1]);
	}
	else
	{
		dup2(var->st_in, 0);
		dup2(var->st_out, 1);
		close(var->end[0]);
		close(var->end[1]);
	}
	var->br = 0;
	var->c = 0;
	var->c2 = 0;
}

int	count_pipe(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->tokn == PIPE)
			i++;
		lst = lst->next;
	}
	return (i + 1);
}

int	c_pip(char **str, t_cd *cd, t_list *node)
{
	t_vars	var;
	int		pipe;

	pipe = count_pipe(node);
	inisial(&var, str);
	while (++var.i < pipe)
	{
		var.fd[1] = 0;
		var.fd[0] = 0;
		ft_check_redi_p(&var, var.str[var.i], node);
		if (!var.br)
			ft_ex_com_pipe(&var, cd, node);
		ft_dup_p(&var);
		ft_change_node(&node);
	}
	ft_fre(str);
	return (ft_wait_p(&var));
}
