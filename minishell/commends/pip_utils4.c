/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:41:10 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/23 20:51:40 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_change_node(t_list **node)
{
	while ((*node)->tokn != PIPE && (*node))
	{
		if ((*node)->next->tokn == END_TOKN)
			break ;
		(*node) = (*node)->next;
	}
	(*node) = (*node)->next;
}

int	ft_check_red(t_list *node, int fd)
{
	int	i;

	while (node->tokn != PIPE)
	{
		if (node->tokn == OREDI)
		{
			node = node->next;
			fd = open(node->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
				i = 1;
		}
		else if (node->tokn == IREDI)
		{
			node = node->next;
			fd = open(node->data, O_RDONLY);
				i = 0;
		}
		node = node->next;
	}
	return (i);
}

int	ft_check_red2(t_list *node, int fd)
{
	while (node->tokn != PIPE && node)
	{
		if (node->tokn == OREDI)
		{
			node = node->next;
			fd = open(node->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
		}
		else if (node->tokn == IREDI)
		{
			node = node->next;
			fd = open(node->data, O_RDONLY);
		}
		node = node->next;
	}
	return (fd);
}

int	ft_oredi_p(t_vars *var, t_list	**head, char *str)
{
	var->file_n = ft_strdup("");
	(*head) = (*head)->next;
	if ((*head)->tokn == WS)
		(*head) = (*head)->next;
	while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
	{
		var->file_n = ft_strjoin(var->file_n, (*head)->data);
		(*head) = (*head)->next;
	}
	var->fd[1] = open(var->file_n, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (var->fd[1] == -1 || !var->file_n)
	{
		perror("Error");
		free(var->file_n);
		var->br = 1;
		return (0);
	}
	var->br = ft_check_nul_cm(str);
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}

int	ft_outputh_p(t_vars *var, t_list	**head, char *str)
{
	var->file_n = ft_strdup("");
	(*head) = (*head)->next;
	if ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
		(*head) = (*head)->next;
	while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
	{
		var->file_n = ft_strjoin(var->file_n, (*head)->data);
		(*head) = (*head)->next;
	}
	var->fd[1] = open(var->file_n,
			O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (var->fd[1] == -1 || !var->file_n)
	{
		perror("Error");
		free(var->file_n);
		var->br = 1;
		return (0);
	}
	var->br = ft_check_nul_cm(str);
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}
