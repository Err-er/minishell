/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:42:18 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/24 20:23:50 by zait-sli         ###   ########.fr       */
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

int	skip_flags(t_list *node, int j)
{
	int	i;

	i = 0;
	if (node->tokn == WS && j == 0)
		return (1);
	if (node->data[i] == '-' && node->data[i + 1] == 'n')
		i++;
	while (node->data[i] && node->data[i] == 'n')
		i++;
	if (node->data[i] == 'n' || !node->data[i])
		return (1);
	return (0);
}

void	ft_skip_redi(t_list **node, int i)
{
	if ((*node)->tokn == WS && ((*node)->next->tokn == IREDI
			|| (*node)->next->tokn == OREDI || (*node)->next->tokn == OUTPUT_H
			|| (*node)->next->tokn == INPUT_H))
		(*node) = (*node)->next;
	if ((*node)->tokn == IREDI || (*node)->tokn == OREDI
		|| (*node)->tokn == OUTPUT_H || (*node)->tokn == INPUT_H)
	{
		(*node) = (*node)->next;
		if ((*node)->tokn == WS)
			(*node) = (*node)->next;
		if ((*node)->tokn == WR)
			(*node) = (*node)->next;
		if ((*node)->tokn == LIMITER)
			(*node) = (*node)->next;
		if ((*node)->tokn == WS)
			(*node) = (*node)->next;
	}
	if ((*node)->tokn == WS && !i)
		(*node) = (*node)->next;
}

void	ft_echo_flag(t_list *node)
{
	int	i;

	i = 0;
	if (node->tokn == WS)
		node = node->next;
	while (node->tokn != END_TOKN && node->tokn != PIPE)
	{
		ft_skip_redi(&node, 1);
		if (i == 0)
		{
			while (skip_flags(node, 1))
				node = node->next;
		}
		if (node->tokn == PIPE)
			break ;
		if (node->data)
			ft_putstr(node->data);
		node = node->next;
	}
}

void	ft_echo_utils(t_list *node)
{
	while (node && node->tokn != END_TOKN && node->tokn != PIPE)
	{
		ft_skip_redi(&node, 1);
		if (node->tokn == PIPE)
			break ;
		if (node->data && node->tokn != END_TOKN)
			ft_putstr(node->data);
		node = node->next;
	}
	printf("\n");
}
