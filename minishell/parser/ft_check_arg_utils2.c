/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:40:00 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/25 20:41:17 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstlast(head);
		head -> next = new;
	}
	else
		*lst = new;
}

t_list	*ft_lstnew(char *value, int tokn)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = value;
	new->tokn = tokn;
	new->next = NULL;
	return (new);
}

int	ft_parser_edit(t_list **node, char *input, int i)
{
	int		j;

	j = i;
	if (input[j] == '\'' && input[j + 1] == '\'')
	{
		if (ft_isprint(input[j - 1]) && input[j - 1] != ' ')
			return (0);
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(""), NUL)), 0);
	}
	while (input[++j])
	{
		if (input[j] == '\'')
			break ;
	}
	if (input[j] == '\'')
	{
		i++;
		ft_lstadd_back(node, ft_lstnew(ft_substr(input, i, j - i), WR));
		return (j - i + 1);
	}
	return (printf("single quotes not closed\n"), -1);
}

int	ft_parser_edit1_utils(t_list **node, char *input, t_data *var, char **env)
{
	var->str = ft_substr(input, var->i, var->j - var->i);
	var->x = var->i;
	if (ft_strchr(var->str, '$'))
	{
		var->c = var->i - 1;
		while (++var->c < var->j)
		{
			if (input[var->c] == '$')
			{
				if (var->c - var->x)
					ft_lstadd_back(node, ft_lstnew(ft_substr(input,
								var->x, var->c - var->x), WR));
				var->c += ft_expand(node, input, env, var->c);
				var->x = var->c;
				var->c--;
			}
		}
		if (var->j - var->x)
			ft_lstadd_back(node,
				ft_lstnew(ft_substr(input, var->x, var->j - var->x), WR));
		free(var->str);
	}
	else
		ft_lstadd_back(node, ft_lstnew(var->str, WR));
	return (var->j - var->i + 1);
}

int	ft_parser_edit1(t_list **node, char *input, int i, char **env)
{
	t_data	var;

	var.j = i;
	var.i = i;
	if (input[var.j] == '"' && input[var.j + 1] == '"')
	{
		if (ft_isprint(input[var.j - 1]) && input[var.j - 1] != ' ')
			return (0);
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(""), NUL)), 0);
	}
	while (input[++var.j])
	{
		if (input[var.j] == '"')
			break ;
	}
	if (input[var.j] == '"')
	{
		var.i++;
		return (ft_parser_edit1_utils(node, input, &var, env));
	}
	return (printf("double quotes not closed\n"), -1);
}
