/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:01:24 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/25 00:44:28 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_cp(char **menv, char **nenv, char *s)
{
	int		i;
	int		x;
	char	**t;

	i = 0;
	x = 0;
	while (menv && menv[i])
	{
		t = ft_split_2(menv[i], '=');
		if (t[0] && !ft_strcmp(s, t[0]))
		{
			i++;
			if (!menv[i])
				break ;
		}
		ft_fre(t);
		nenv[x] = ft_strdup(menv[i]);
		i++;
		x++;
	}
	nenv[x] = NULL;
	return (nenv);
}

void	unset_this(t_cd *cd, char *s)
{
	char	**new_env;
	int		i;

	i = 0;
	while (cd->my_env && cd->my_env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	new_env = ft_cp(cd->my_env, new_env, s);
	ft_fre(cd->my_env);
	cd->my_env = new_env;
}

int	check_valid_unset(char *s, char **env)
{
	int		i;
	char	**t;

	i = -1;
	while (s[++i])
	{
		if ((s[i] < 65 && s[i] != 32)
			|| s[i] > 122 || (s[i] >= 91 && s[i] <= 94) || s[i] == 96)
			return (
				printf("minishell: unset: `%s': not a valid identifier\n",
					s), 1);
	}
	i = -1;
	while (env && env[++i])
	{
		t = ft_split_2(env[i], '=');
		if (t[0] && !ft_strcmp(t[0], s))
			return (ft_fre(t), 1);
		ft_fre(t);
	}
	return (0);
}

void	exec_unset(t_cd *cd, t_list *head)
{
	while (head->next->tokn != END_TOKN || head->next->tokn != ST_TOKN)
	{
		if (check_valid_unset(head->next->data, cd->my_env))
			unset_this(cd, head->next->data);
		head = head->next;
	}
}

void	ft_unset(t_list **node, t_cd *cd)
{
	t_list	*head;

	head = *node;
	head = head->next;
	while (1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break ;
	}
	if (!head->next->data)
	{
		g_ds = 1;
		ft_putstr_fd("minishell: unset: `': not a valid identifier\n", 2);
		return ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
		return ;
	else
		exec_unset(cd, head);
}
