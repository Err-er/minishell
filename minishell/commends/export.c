/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:57 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/24 22:47:22 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(int tokn)
{
	if (tokn == END_TOKN || tokn == ST_TOKN || tokn == PIPE || tokn == OREDI
		|| tokn == IREDI || tokn == OUTPUT_H || tokn == INPUT_H)
	{		
		return (1);
	}
	else
		return (0);
}

void	exex_export(t_list *head, t_cd *cd)
{
	char	*temp;

	temp = ft_strdup(head->next->data);
	temp = ft_strtrim2(temp, " ");
	while (head->next->next->tokn == WR
		|| head->next->next->tokn == NUL)
	{
		if (head->next->next->tokn == WR)
		{
			head = head->next;
			temp = ft_strjoin(temp, head->next->data);
		}
		else
			head = head->next;
	}
	if (check_valid(temp, cd->my_env))
	{	
		if (ft_check_addition(temp) && check_exist(temp, cd->my_env))
			add_this(cd, temp);
		else if (!check_exist(temp, cd->my_env) && head->next->tokn != WS)
			export_this(cd, temp);
		else if (check_exist(temp, cd->my_env) && head->next->tokn != WS)
			replace_this(cd, temp);
	}
	free (temp);
}

void	handle_expo(t_list *head, t_cd *cd)
{
	while (head && (head->next->tokn != END_TOKN))
	{
		while ((head->next->tokn == WS || head->next->tokn == NUL)
			&& head->next->tokn != END_TOKN)
			head = head->next;
		if (!head->next->data || head->next->tokn == NUL
			|| (head->tokn == NUL && head->next->tokn == END_TOKN))
		{
			g_ds = 1;
			printf("minishell: export: `': not a valid identifier\n");
			return ;
		}
		else
			exex_export(head, cd);
		if (head->next)
			head = head->next;
	}
}

void	ft_export(t_list **node, t_cd *cd)
{
	t_list	*head;

	head = (*node);
	head = head->next;
	while (1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break ;
	}
	if (check_token(head->next->tokn))
	{
		g_ds = 0;
		ft_print_export(cd);
		return ;
	}
	else
		handle_expo(head, cd);
}
