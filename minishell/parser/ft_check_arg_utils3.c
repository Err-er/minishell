/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/26 13:19:12 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isalpha(char c)
{
	if (c < 65 || c > 122 || (c < 97 && c > 90))
	{
		if (c != '_')
			return (0);
	}
	return (1);
}

int	ft_expand_utils(t_list **node, char *input, char **env, int i)
{
	int		j;
	char	*str;
	char	*s;

	j = i + 1;
	while (ft_isalpha(input[j]) || ft_isdigit(input[j]))
	{
		if (ft_isdigit(input[j]) && (i + 1) == j)
		{
			j++;
			break ;
		}
		j++;
	}
	s = ft_substr(input, i + 1, j - (i + 1));
	str = get_path(env, s);
	free(s);
	str = ft_strtrim(str, "\"");
	if (str)
		ft_lstadd_back(node, ft_lstnew(str, WR));
	return (j - i);
}

int	ft_expand(t_list **node, char *input, char **env, int i)
{
	int		j;

	j = 0;
	if (!input[i + 1] || input[i + 1] == ' ')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup("$"), WR)), 2);
	else if (input[i + 1] == '?')
		return (ft_lstadd_back(node,
				ft_lstnew(ft_strdup(ft_itoa(g_ds)), WR)), 2);
	else if ((input[i + 1] == '"' && input[i + 2] == '"')
		|| (input[i + 1] == '\'' && input[i + 2] == '\''))
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(""), WR)), 3);
	else if (input[i + 1] == '"' || input[i + 1] == '\'')
		return (1);
	else if ((!ft_isalpha(input[i + 1]) && !ft_isdigit(input[i + 1])))
		return (2);
	else
		return (ft_expand_utils(node, input, env, i));
}

void	ft_lstclear(t_list **lst)
{
	t_list	*head;

	if (!lst)
		return ;
	while (*lst)
	{
		head = *lst;
		*lst = (*lst)->next;
		if (head->data)
			free(head->data);
		free(head);
	}
	*lst = NULL;
}

int	ft_check_pip(t_list *node, int c)
{
	t_list	*head;

	head = node;
	while (head)
	{
		if (head->tokn == c)
			return (1);
		head = head->next;
	}
	return (0);
}
