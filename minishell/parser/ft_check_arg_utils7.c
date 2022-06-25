/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_utils7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/23 21:01:51 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_nul(t_list **head, int i)
{
	while ((*head)->tokn == NUL && (*head)->next->tokn == NUL)
		(*head) = (*head)->next;
	if ((*head)->tokn == NUL && i == 0 && (*head)->next->tokn == 0)
		(*head) = (*head)->next;
}

char	*mini_utils(t_list **head, char *str)
{
	skip_nul(head, 1);
	if ((*head)->next->tokn == WS
		|| (*head)->next->tokn == END_TOKN || (*head)->next->tokn == PIPE)
		str = ft_strjoin(str, " ");
	(*head) = (*head)->next;
	return (str);
}

char	*ft_ex_com_utils(t_list *head, t_vars *var, char *str)
{
	while (head)
	{
		if (head->tokn == WS)
		{
			str = ft_strjoin(str, "\v");
			head = head->next;
		}
		else if (head->tokn == NUL)
			str = mini_utils(&head, str);
		else if (head->tokn == WR)
		{
			str = ft_strjoin(str, head->data);
			head = head->next;
			skip_nul(&head, 0);
		}
		else if (!ft_ex_com_utils1(&head, var))
			return (free(str), free(var->file_n), perror("Error"), NULL);
	}
	if (!str[0])
		return (free(str), NULL);
	return (str);
}

void	ft_ex_com_utils2(t_list *node, t_cd *cd, t_vars	var, char *str)
{
	int		ex;

	var.node = node;
	get_global(1);
	var.c2 = fork();
	if (var.c2 == 0)
		ft_ex(str, cd, var);
	waitpid(var.c2, &ex, 0);
	utils_ex_ds(ex);
}

t_list	*new_node_export(t_list	*node)
{
	t_list	*n_node;
	t_list	*tmp;

	n_node = ft_lstnew(ft_strdup("->"), ST_TOKN);
	tmp = node->next;
	while (tmp)
	{
		if (tmp->tokn == WS && (tmp->tokn == OREDI || tmp->tokn == OUTPUT_H
				|| tmp->tokn == IREDI || tmp->tokn == INPUT_H))
			tmp = tmp->next;
		if (tmp->tokn == OREDI || tmp->tokn == OUTPUT_H
			|| tmp->tokn == IREDI || tmp->tokn == INPUT_H)
		{
			tmp = tmp->next;
			if (tmp->tokn == WS)
				tmp = tmp->next;
			tmp = tmp->next;
		}
		ft_lstadd_back(&n_node, ft_lstnew(ft_strdup(tmp->data), tmp->tokn));
		tmp = tmp->next;
	}
	return (n_node);
}
