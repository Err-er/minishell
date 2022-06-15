/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:20:16 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/15 11:51:41 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char	*c)
{
	int		i;

	i = 0;
	while (c[i] != '\0')
	{
		write(1, &c[i], 1);
		i++;
	}
}

void	ft_echo_flag(t_list *node)
{
	while (node->tokn != END_TOKN && node->tokn != PIPE)
	{
		if (node->tokn == WS && (node->next->tokn == IREDI
				|| node->next->tokn == OREDI || node->next->tokn == OUTPUT_H
				|| node->next->tokn == INPUT_H))
			node = node->next;
		if (node->tokn == IREDI || node->tokn == OREDI
			|| node->tokn == OUTPUT_H || node->tokn == INPUT_H)
		{
			node = node->next;
			while (node->tokn == WS)
				node = node->next;
			if (node->tokn == WR)
				node = node->next;
			if (node->tokn == LIMITER)
				node = node->next;
		}
		if (node->data)
			ft_putstr(node->data);
		node = node->next;
	}
}

void	ft_echo_utils(t_list *node, int i)
{
	if (i == 1)
	{
		node = node->next;
		node = node->next;
	}
	while (node && node->tokn != END_TOKN && node->tokn != PIPE)
	{
		if (node->tokn == WS && (node->next->tokn == IREDI
				|| node->next->tokn == OREDI || node->next->tokn == OUTPUT_H
				|| node->next->tokn == INPUT_H))
			node = node->next;
		if (node->tokn == IREDI || node->tokn == OREDI
			|| node->tokn == OUTPUT_H || node->tokn == INPUT_H)
		{
			node = node->next;
			while (node->tokn == WS)
				node = node->next;
			if (node->tokn == WR)
				node = node->next;
			if (node->tokn == LIMITER)
				node = node->next;
		}
		if (node->data && node->tokn != END_TOKN)
			ft_putstr(node->data);
		node = node->next;
	}
	printf("\n");
}

int	skip_flags(t_list *node)
{
	int	i;

	i = 0;
	if (node->tokn == WS)
		return (1);
	if (node->data[i] == '-')
		i++;
	while (node->data[i] && node->data[i] == 'n')
		i++;
	if (node->data[i] == 'n' || !node->data[i])
		return (1);
	return (0);
}

int	check_flags(t_list *node)
{
	int i;

	i = 0;
	if (node->data[i] == '-')
		i++;
	while (node->data[i] && node->data[i] == 'n')
		i++;
	if (node->data[i] == 'n' || !node->data[i])
		return (1);
	return (0);
}

void	ft_echo(t_list *node)
{
	int		i;
	t_list	*head;

	head = node;
	while (head)
	{
		if (!ft_strcmp(head->data, "echo"))
		{
			if (head->next->tokn == END_TOKN || head->next->next->tokn == END_TOKN)
				write(1, "\n", 1);
			else if (head->next->next->data
				&& !ft_strncmp(head->next->next->data, "-n", 2))
			{
				head = head->next->next;
				if ((head->next->tokn == WS || !head->next->tokn)
					&& (!ft_strcmp(head->data, "-n") || check_flags(head)))
				{
					while (skip_flags(head))
						head = head->next;
					if (!head->tokn)
						return ;
					ft_echo_flag(head);
				}
				else
					ft_echo_utils(head, 0);
			}
			else
				ft_echo_utils(head, 1);
			ft_lstclear(&node);
			return ;
		}
		head = head->next;
	}
}
