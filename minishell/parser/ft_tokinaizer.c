/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokinaizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:36:41 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/25 20:37:39 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_tok_mini_utils1(t_list **node, char *input, char **env, t_data *var)
{
	if (input[var->i] == ' ')
	{
		if (input[var->i + 1] != '|')
		{	
			while (input[var->i] == ' ')
				var->i++;
			if (!input[var->i])
				return (1);
			ft_lstadd_back(node, ft_lstnew(ft_strdup(" "), WS));
			var->i--;
		}
		return (1);
	}
	else if (input[var->i] == '|')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup("|"), PIPE)), 1);
	else if (input[var->i] == '"')
	{
		var->j = ft_parser_edit1(node, input, var->i, env);
		if (var->j == -1)
			return (var->x = 1, 0);
		var->i += var->j + 1;
		return (1);
	}
	return (-1);
}

int	ft_tok_mini_utils2(t_list **node, char *input, char **env, t_data *var)
{
	if (input[var->i] == '\'')
	{
		var->j = ft_parser_edit(node, input, var->i);
		if (var->j == -1)
			return (var->x = 1, 0);
		var->i += var->j + 1;
		return (1);
	}
	else if (input[var->i] == '$')
	{
		var->i += ft_expand(node, input, env, var->i);
		var->j = 2;
		return (1);
	}
	else if (input[var->i] == '>' && input[var->i + 1] == '>')
	{
		var->i += 1;
		ft_lstadd_back(node, ft_lstnew(ft_strdup(">>"), OUTPUT_H));
		return (1);
	}
	else if (input[var->i] == '>')
		return (ft_lstadd_back(node, ft_lstnew(ft_strdup(">"), OREDI)), 1);
	return (-1);
}

int	ft_tok_mini_utils3(t_list **node, char *input, t_data *var)
{
	if (input[var->i] == '<' && input[var->i + 1] == '<')
	{
		if (!ft_tok_input_h(node, input, var))
			return (var->x = 1, 0);
		return (1);
	}
	else if (input[var->i] == '<')
		ft_lstadd_back(node, ft_lstnew(ft_strdup("<"), IREDI));
	else
	{
		if (input[var->i] != ' ')
		{
			var->i--;
			while (check_str(input, ++var->i) && input[var->i] != '|')
				var->j++;
			ft_lstadd_back(node,
				ft_lstnew(ft_substr(input, var->i - var->j, var->j), WR));
		}
		return (1);
	}
	return (-1);
}

int	ft_check_tok(t_list **node, char *input, char **env, t_data *var)
{
	if (ft_tok_mini_utils1(node, input, env, var) != -1)
	{
		if (var->x == 1)
			return (0);
	}
	else if (ft_tok_mini_utils2(node, input, env, var) != -1)
	{
		if (var->x == 1)
			return (0);
	}
	else if (ft_tok_mini_utils3(node, input, var) != -1)
	{
		if (var->x == 1)
			return (0);
	}
	return (1);
}

int	ft_tokinaizer(t_list **node, char *input, char **env)
{
	t_data	var;

	var.j = 1;
	var.i = 0 ;
	while (input[var.i] == ' ')
		var.i++;
	while (var.i < ft_strlen(input))
	{
		var.j = 0;
		if (!ft_check_tok(node, input, env, &var))
			return (0);
		if (!var.j)
			var.i++;
	}
	ft_lstadd_back(node, ft_lstnew(strdup("<-"), END_TOKN));
	return (1);
}
