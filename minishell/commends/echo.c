/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:20:16 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/21 17:23:45 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_echo_flag(t_list **node)
{
	while((*node)->tokn != EN_TOKN && (*node)->tokn != PIP && (*node)->tokn != Iredi && (*node)->tokn != Oredi)
	{
		if((*node)->tokn == WS && ((*node)->next->tokn == WS || (*node)->next->tokn == PIP || (*node)->next->tokn == Iredi || (*node)->next->tokn == Oredi))
			return ;
		else if((*node)->data)
			printf("%s", (*node)->data);
		(*node) = (*node)->next;
	}
}

void    ft_echo_utils(t_list **node)
{

	(*node) = (*node)->next;
	while((*node)->tokn != EN_TOKN  && (*node)->tokn != PIP && (*node)->tokn != Iredi && (*node)->tokn != Oredi)
	{
		if((*node)->data)
			printf("%s", (*node)->data);
		(*node) = (*node)->next;
	}
	puts("");
}

int	skip_flags(t_list  *node)
{
	int i;

	i = 0;
	if(node->tokn == WS)
		return(1);
	if(node->data[i] == '-')
		i++;
	while(node->data[i] && node->data[i] == 'n')
		i++;
	if (node->data[i] == 'n' || !node->data[i])
		return (1);
	printf("i   : %d\n", i);
	return (0);
}
void    ft_echo(t_list **node)
{
	int     i;
	t_list *head;

	head = *node;
	while(head)
	{
		if(!ft_strcmp(head->data, "echo"))
		{
			if(head->next->next->data && !ft_strncmp(head->next->next->data, "-n", 2))
			{
				if(!ft_strncmp(head->next->next->data, "-n", 2))
				{
					head = head->next->next;
					while(skip_flags(head))
						head = head->next;
					ft_echo_flag(&head);
				}
			}
			else
				ft_echo_utils(&head);
			ft_lstclear(node);
			node = &head;
			return ;
		}
		head = head->next;
	}
}