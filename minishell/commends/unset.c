/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:01:24 by zait-sli          #+#    #+#             */
/*   Updated: 2022/05/27 23:43:54 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_this(t_cd *cd, char *s)
{
	char **new_env;
	int i;
	int x;

	cd->env_len--;
	new_env = malloc(sizeof(char *) * cd->env_len);

	i = 0;
	x = 0;
	char **t;
	while(cd->my_env[i])
	{
		t = ft_split_2(cd->my_env[i],'=');
		if (t[0] && !ft_strcmp(s, t[0]))
		{
			i++;
			if (!cd->my_env[i])
				break;
		}
		ft_fre(t);
		new_env[x] = ft_strdup(cd->my_env[i]);
		i++;
		x++;
	}
	new_env[x] = NULL;
	free(cd->my_env);
	cd->my_env = new_env;
}

int	check_valid_unset(char *s,char **env)
{
	int i = 0;
	char **t;
	
	while(env[i])
	{
		t = ft_split_2(env[i],'=');
		if (t[0] && !ft_strcmp(t[0],s))
		{
			ft_fre(t);
			return(1);
		}
		ft_fre(t);
		i++;
	}
	return(0);
}

void	ft_unset(t_list **node, t_cd *cd)
{
	t_list *head;

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
		return ;
	else
	{
		while(head->next->tokn != END_TOKN || head->next->tokn != ST_TOKN)
		{
			if (check_valid_unset(head->next->data,cd->my_env))
				unset_this(cd, head->next->data);
			head = head->next;
		}
	}
}