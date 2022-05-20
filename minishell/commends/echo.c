/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:20:16 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/20 20:34:36 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_echo_flag(t_list *node)
{
    node = node->next;
    node = node->next;
    while(node->tokn != EN_TOKN && node->tokn != PIP && node->tokn != Iredi && node->tokn != Oredi)
    {
        if(node->tokn == WS && (node->next->tokn == WS || node->next->tokn == PIP || node->next->tokn == Iredi || node->next->tokn == Oredi))
            return ;
        else if(node->data)
            printf("%s", node->data);
        node = node->next;
    }
}

void    ft_echo_utils(t_list *node)
{

    node = node->next;
    node = node->next;
    while(node->tokn != EN_TOKN  && node->tokn != PIP && node->tokn != Iredi && node->tokn != Oredi)
    {
        if(node->data)
            printf("%s", node->data);
        node = node->next;
    }
    puts("");
}

void    ft_echo(t_list *node)
{
    int     i;
    t_list *head;

    head = node;
    while(head)
    {
        if(!ft_strcmp(head->data, "echo"))
        {
            if (head->next->tokn == EN_TOKN)
            {
                puts("");
                return;
            }
            if(head->next->next->data && !ft_strncmp(head->next->next->data, "-n", 2))
                ft_echo_flag(head->next->next);
            else
                ft_echo_utils(head);
            return ;
        }
        head = head->next;
    }
}