/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:32:23 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/10 05:21:33 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_isdigit(char *s)
{
	int	i = 0;

	while (s[i])
	{
		if ((s[i] == '-' || s[i] == '+') && i == 0)
			i++;
		if ((s[i] < 48 || s[i] > 57))
			return (0);
		i++;
	}
	return (1);
}

int	check_len(char *s)
{
	int	j = 0;
	int	x;

	while (s[j])
	{
		if ((s[j] == '-' || s[j] == '+') && j == 0)
		{
			j++;
			x = j;
			while (s[x] == '0')
				x++;
			j = x;
		}
		if (s[j])
			j++;
	}
	return (j);
}

int check_near_max(char *s)
{
	char *min = "9223372036854775808";
	char *max = "9223372036854775807";
	if (check_len(s) == 19)
	{
		if (s[0] == '-')
		{
			if (ft_strcmp(&s[1],min) > 0)
				return(0);
			else
				return(1);
		}
		else
		{
			if (ft_strcmp(s,max) > 0)
				return(0);
			else
				return(1);
		}
	}
	return(1);
}

void	ft_exit(t_list **node)
{
	t_list *head;
	long long nb;

	head = *node;
	head = head->next;

	while(1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break  ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
	{
		printf("exit\n");
		exit(ds);
		return ;
	}
	if (head->next->next->tokn != END_TOKN && head->next->next->tokn != ST_TOKN && head->next->next->tokn != PIPE)
	{	
		printf("minishell : exit: too many arguments\n");
		ds = 1;
		return ;
	}
	if (head->next->data)
	{
		if (check_isdigit(head->next->data) && check_len(head->next->data) <=19 && check_near_max(head->next->data))
		{
			printf("exit\n");
			exit(ds);	
		}
		else
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n",head->next->data);
			exit(ds);
		}
	}
}