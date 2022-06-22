/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_utils6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/22 10:35:31 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_ex_oredi(t_list **head, t_vars	*var)
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
	if (var->fd[1] == -1 || !var->file_n[0])
		return (0);
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}

void	remove_ctlc(void)
{
	struct termios	terminal;
	struct termios	terminal2;

	tcgetattr(0, &terminal);
	terminal2 = terminal;
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW | TCSAFLUSH, &terminal);
	get_term(terminal2, 1);
}

struct termios	get_term(struct termios term, int i)
{
	static struct termios	terminal;

	if (i)
		terminal = term;
	return (terminal);
}

int	ft_ex_iredi(t_list **head, t_vars	*var)
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
	var->fd[0] = open(var->file_n, O_RDONLY);
	if ((var->fd[0] == -1 || !var->file_n) && (*head)->tokn != 16)
		return (0);
	free(var->file_n);
	var->x[0] = 0;
	return (1);
}

int	ft_ex_com_utils1(t_list **head, t_vars *var)
{
	if ((*head)->tokn == OREDI)
	{
		if (!ft_ex_oredi(head, var))
			return (0);
	}
	else if ((*head)->tokn == OUTPUT_H)
	{
		if (!ft_ex_output_h(head, var))
			return (0);
	}
	else if ((*head)->tokn == INPUT_H)
		ft_ex_input_h(head, var);
	else if ((*head)->tokn == IREDI)
	{
		if (!ft_ex_iredi(head, var))
			return (0);
	}
	else
		(*head) = (*head)->next;
	return (1);
}
