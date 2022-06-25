/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:12:33 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/24 20:32:47 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (ft_lstlast(lst->next));
}

int	ft_ex_output_h(t_list **head, t_vars	*var)
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
	var->fd[1] = open(var->file_n, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (var->fd[1] == -1 || !var->file_n[0])
		return (0);
	free(var->file_n);
	var->x[1] = 1;
	return (1);
}

void	ft_firts(t_list **head, t_vars *var, t_mini *varr, struct termios *term)
{
	term->c_ispeed = 0;
	var->value = NULL;
	(*head) = (*head)->next;
	while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
		(*head) = (*head)->next;
	get_global3(1);
	varr->pid = fork();
	if (varr->pid == -1)
		exit(127);
	varr->fd_h = open(HERE_D, O_CREAT | O_RDWR, 0777);
}

void	ft_second(t_list **head, t_mini *varr, struct termios *term)
{
	get_global2(30);
	rl_catch_signals = 1;
	remove_ctlc();
	while (1)
	{
		varr->p = readline("> ");
		if (!ft_strcmp2(varr->p, (*head)->data))
		{
			free(varr->p);
			break ;
		}
		ft_putstr_fd(varr->p, varr->fd_h);
		ft_putstr_fd("\n", varr->fd_h);
		free(varr->p);
	}
	(*term) = get_term((*term), 0);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

int	ft_ex_input_h(t_list **head, t_vars *var)
{
	t_mini			varr;
	struct termios	term;

	ft_firts(head, var, &varr, &term);
	if (varr.pid == 0)
	{
		ft_second(head, &varr, &term);
		exit(0);
	}
	get_global2(0);
	waitpid(varr.pid, NULL, 0);
	while (1)
	{
		varr.p2 = get_next_line(varr.fd_h);
		if (!varr.p2)
			break ;
		var->value = ft_strjoin(var->value, varr.p2);
		free(varr.p2);
	}
	free(varr.p2);
	unlink(HERE_D);
	return (1);
}
