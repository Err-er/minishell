/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:20:16 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/24 20:22:31 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flags(t_list *node)
{
	int	i;

	i = 0;
	if (node->data[i] == '-')
		i++;
	while (node->data[i] && node->data[i] == 'n')
		i++;
	if (node->data[i] == 'n' || !node->data[i])
		return (1);
	return (0);
}

void	ft_mini_utils(t_list *head)
{
	if ((head->next->tokn == WS || !head->next->tokn)
		&& (!ft_strcmp(head->data, "-n") || check_flags(head)))
	{
		while (skip_flags(head, 0))
			head = head->next;
		if (!head->tokn)
			return ;
		ft_echo_flag(head);
	}
	else
		ft_echo_utils(head);
}

void	ft_echo(t_list *node)
{
	t_list	*head;

	head = node;
	while (head)
	{
		if (!ft_strcmp(head->data, "echo"))
		{
			head = head->next;
			ft_skip_redi(&head, 0);
			if (node->tokn == PIPE)
				break ;
			if (head->tokn == 0)
				write(1, "\n", 1);
			else if (head->data
				&& !ft_strncmp(head->data, "-n", 2))
				ft_mini_utils(head);
			else
				ft_echo_utils(head);
			ft_lstclear(&node);
			return ;
		}
		head = head->next;
	}
}
