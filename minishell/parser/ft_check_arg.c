/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/22 10:40:23 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_sc(t_list *node)
{
	char	*str;
	char	**cmd;

	str = ft_sc_utils(node);
	if (!str)
		return (0);
	cmd = ft_split_2(str, '\v');
	free(str);
	if (!ft_strcmp(cmd[0], "cd"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_fre(cmd), 1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_fre(cmd), 1);
	return (ft_fre(cmd), 0);
}

void	utils_ex_ds(int ex)
{
	if (WIFEXITED(ex))
	{
		if (ex == 65280)
			g_ds = 255;
		else
			g_ds = ex % 255;
	}
	else if (WIFSIGNALED(ex))
		g_ds = ex + 128;
	if (g_ds == 130)
		write (1, "\n", 1);
	else if (g_ds == 131)
		write(1, "Quit: 3\n", 9);
}

void	ft_pipe_ex(t_list *node, t_cd *cd)
{
	int		pid;
	int		ex;

	get_global(1);
	pid = fork();
	if (pid == 0)
	{
		ex = ft_pip(node, cd);
		if (WIFEXITED(ex))
		{
			if (ex == 65280)
				g_ds = 255;
			else
				g_ds = ex % 255;
		}
		else if (WIFSIGNALED(ex))
			g_ds = ex + 128;
		if (g_ds == 130)
			write(1, "\n", 1);
		else if (g_ds == 131)
			write(1, "Quit: 3\n", 9);
		exit(g_ds);
	}
	waitpid(pid, &ex, 0);
	utils_ex_ds(ex);
}

t_list	*new_node(t_list	*node)
{
	t_list	*n_node;
	t_list	*tmp;
	char	*str;

	n_node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	tmp = node->next;
	while (tmp)
	{
		if (tmp->tokn == WR)
		{
			str = ft_strdup("");
			while (tmp->tokn == WR)
			{
				str = ft_strjoin(str, tmp->data);
				tmp = tmp->next;
			}
			ft_lstadd_back(&n_node, ft_lstnew(ft_strdup(str), WR));
			free (str);
		}
		ft_lstadd_back(&n_node, ft_lstnew(ft_strdup(tmp->data), tmp->tokn));
		tmp = tmp->next;
	}
	return (n_node);
}

int	ft_parser(char *input, t_cd *cd)
{
	int		i;
	t_list	*node;
	t_list	*n_node;

	i = 0;
	if (input[0] == '\0')
		return (1);
	node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	if (!ft_tokinaizer(&node, input, cd->my_env))
		return (0);
	if (!ft_check_syntax(input))
		return (ft_lstclear(&node), 0);
	if (node->tokn == node->next->tokn)
		return (ft_lstclear(&node), 0);
	n_node = new_node(node);
	ft_lstclear(&node);
	if (ft_check_pip(n_node, PIPE))
		ft_pipe_ex(n_node, cd);
	else if (ft_sc(n_node) == 1)
		ft_ex_sc(n_node, cd);
	else if (!ft_sc(n_node))
		ft_ex_com(n_node, cd);
	ft_lstclear(&n_node);
	return (1);
}
