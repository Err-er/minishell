/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:33:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/05 13:06:19 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	print_error(int i)
{
	if (i == 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (i == 2)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
}

int	ft_check_syntax(t_list	*node, char *input)
{
	t_list	*head;
	int		i;

	i = 0;
	while (input[i] == ' ' && input[i])
		i++;
	if (input[i] == '<' && input[i + 1] == '<')
	{
		i += 2;
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			return (print_error(1), 0);
		else
			return (1);
	}
	head = node;
	while (head)
	{
		if ((head->tokn == ST_TOKN && head->next->tokn == PIPE))
			return (print_error(2), 0);
		if ((head->next->tokn == END_TOKN && head->tokn == PIPE)
			&& head->next->tokn == END_TOKN)
			return (print_error(2), 0);
		if ((head->tokn == IREDI || head->tokn == OREDI)
			&& head->next->tokn == END_TOKN)
			return (print_error(1), 0);
		if (head->tokn == INPUT_H
			&& (head->next->next->tokn == END_TOKN || head->next->tokn == 0))
			return (print_error(1), 0);
		if (head->tokn == OUTPUT_H && head->next->tokn == 0)
			return (print_error(1), 0);
		head = head->next;
		if (!head->tokn)
			break ;
	}
	return (1);
}
