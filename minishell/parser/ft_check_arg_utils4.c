/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_utils4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/26 13:11:32 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_check_pip3(t_list *node, int c, int c2)
{
	t_list	*head;

	head = node;
	while (head && head->tokn != c2 && head->tokn != PIPE)
	{
		if (head->tokn == c)
			return (1);
		head = head->next;
	}
	return (0);
}

int	ft_check_pip2(t_list *node, int c)
{
	t_list	*head;

	head = node;
	while (head)
	{
		if (head->tokn == PIPE)
			break ;
		if (head->tokn == c)
			return (1);
		head = head->next;
	}
	return (0);
}

int	ft_is_last(t_list *node, int c, int c2, int end)
{
	t_list	*head;
	int		nb;

	nb = 1;
	head = node;
	if (head->next)
		head = head->next;
	while (head->tokn != end)
	{
		if (head->tokn == c)
			nb = 1;
		else if (head->tokn == c2)
			nb = 0;
		head = head->next;
		if (!head)
			break ;
	}
	return (nb);
}

void	ft_pip_utils_1(t_list **head, char **str)
{
	if ((*head)->tokn == PIPE)
	{
		(*str) = ft_strjoin((*str), "\t");
		(*head) = (*head)->next;
	}
	if ((*head)->tokn == WS)
	{
		(*str) = ft_strjoin((*str), "\v");
		(*head) = (*head)->next;
	}
	if ((*head)->tokn == NUL)
		(*str) = mini_utils(head, (*str));
	if ((*head)->tokn == WR)
	{
		(*str) = ft_strjoin((*str), (*head)->data);
		(*head) = (*head)->next;
		skip_nul(head, 0);
	}
}

void	ft_pip_utils_2(t_list **head, char **str)
{
	if ((*head)->tokn == OREDI)
	{
		(*head) = (*head)->next;
		while ((*head)->tokn == WS)
			(*head) = (*head)->next;
		while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
	}
	if ((*head)->tokn == OUTPUT_H)
	{
		(*head) = (*head)->next;
		while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
		while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
	}
	if ((*head)->tokn == INPUT_H)
	{
		(*head) = (*head)->next;
		while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
			(*head) = (*head)->next;
		if ((*head)->tokn == END_TOKN)
			(*str) = ft_strjoin((*str), "\v");
	}
}
