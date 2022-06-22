/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:57 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/23 00:07:47 by zait-sli         ###   ########.fr       */
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

void	ft_exprot(t_list **node, t_cd *cd)
{
	t_list	*head;
	char	*temp;

	head = (*node);
	head = head->next;
	head = head->next;
	if (check_token(head->next->tokn))
	{
		g_ds = 0;
		ft_print_export(cd);
		return ;
	}
	else
	{
		while (head && (head->next->tokn != END_TOKN
				|| head->next->tokn != ST_TOKN))
		{
			while (head->next->tokn == WS && head->next->tokn != END_TOKN)
				head = head->next;
			while (head->next->tokn == NUL && head->next->tokn != END_TOKN)
				head = head->next;
			if (!head->next->data || head->next->tokn == NUL
				|| (head->tokn == NUL && head->next->tokn == END_TOKN))
			{
				g_ds = 1;
				ft_putstr_fd("minishell: export: `':not a valid identifier\n",
					2);
				return ;
			}
			else
			{
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
					if (ft_check_addition(temp)
						&& check_exist(temp, cd->my_env))
						add_this(cd, temp);
					else if (!check_exist(temp, cd->my_env)
						&& head->next->tokn != WS)
						export_this(cd, temp);
					else if (check_exist(temp, cd->my_env)
						&& head->next->tokn != WS)
						replace_this(cd, temp);
				}
				free (temp);
			}
			if (head->next)
				head = head->next;
		}
	}
}
