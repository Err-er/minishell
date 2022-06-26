/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_utils8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/25 21:55:45 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_ex_export(t_list *head, t_cd *cd, t_vars var)
{
	t_list	*node;

	node = new_node_export(head);
	if (ft_check_pip(head, OUTPUT_H) || ft_check_pip(head, OREDI))
	{
		var.st_out = dup(1);
		dup2(var.fd[1], var.x[1]);
		close(var.fd[1]);
		ft_export(&node, cd);
		dup2(var.st_out, 1);
		close(var.st_out);
	}
	else
		ft_export(&node, cd);
	ft_lstclear(&node);
}

int	ft_ex_com(t_list *node, t_cd *cd)
{
	char	*str;
	char	**cmd;
	t_vars	var;

	var.fd[0] = 0;
	var.fd[1] = 0;
	str = ft_strdup("");
	var.value = NULL;
	str = ft_ex_com_utils(node->next, &var, str);
	if (!str)
		return (free(str), free(var.value), 0);
	cmd = ft_split_2(str, '\v');
	if (!cmd[0] || !cmd[0][0])
		return (ft_fre(cmd), free(str), free(var.value), 0);
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(&node, cd);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_ex_export(node, cd, var);
	else
		ft_ex_com_utils2(node, cd, var, str);
	return (free(str), free(var.value), ft_fre(cmd), 1);
}

void	ft_ex_sc_utils(t_list *node, t_cd *cd, char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(&node, cd);
	else if (!ft_strcmp(cmd, "echo"))
		g_ds = 0;
	else if (!ft_strcmp(cmd, "export"))
		ft_export(&node, cd);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(&node, cd);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_getcwd(cd);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(&node);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(&node, cd);
}

void	ft_ex_sc(t_list *node, t_cd *cd)
{
	t_list	*head;
	char	*str;
	char	**cmd;
	int		c;

	str = malloc(1);
	str[0] = '\0';
	head = node->next;
	c = 0;
	while (head->tokn != END_TOKN)
	{
		if (head->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (head->data)
			str = ft_strjoin(str, head->data);
		head = head->next;
	}
	cmd = ft_split_2(str, '\v');
	ft_ex_sc_utils(node, cd, cmd[0]);
	free(str);
	ft_fre(cmd);
}

char	*ft_sc_utils(t_list *node)
{
	char	*str;

	str = ft_strdup("");
	node = node->next;
	while (node->tokn != END_TOKN)
	{
		if (node->tokn == WS)
			str = ft_strjoin(str, "\v");
		else if (node->tokn == OREDI || node->tokn == IREDI
			|| node->tokn == INPUT_H || node->tokn == OUTPUT_H)
			return (free(str), NULL);
		else if (node->data)
			str = ft_strjoin(str, node->data);
		node = node->next;
	}
	if (!str[0])
		return (NULL);
	return (str);
}
