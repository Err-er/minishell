/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:01:24 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/19 17:36:28 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_this(t_cd *cd, char *s)
{
	char	**new_env;
	int		i;
	int		x;
	char	**t;

	i = 0;
	while (cd->my_env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	x = 0;
	while (cd->my_env[i])
	{
		t = ft_split_2(cd->my_env[i], '=');
		if (t[0] && !ft_strcmp(s, t[0]))
		{
			i++;
			if (!cd->my_env[i])
				break ;
		}
		ft_fre(t);
		new_env[x] = ft_strdup(cd->my_env[i]);
		i++;
		x++;
	}
	new_env[x] = NULL;
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
	while (env[++i])
	{
		t = ft_split_2(env[i], '=');
		if (t[0] && !ft_strcmp(t[0], s))
			return (ft_fre(t), 1);
		ft_fre(t);
	}
	return (0);
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
		printf("minishell: unset: `': not a valid identifier\n");
		return ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
		return ;
	else
	{
		while (head->next->tokn != END_TOKN || head->next->tokn != ST_TOKN)
		{
			if (check_valid_unset(head->next->data, cd->my_env))
				unset_this(cd, head->next->data);
			head = head->next;
		}
	}
}
