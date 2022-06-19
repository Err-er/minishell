/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokinaizer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:36:41 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/19 17:32:07 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_tok_input_h_ut1(char *input, t_data *var)
{
	if (input[var->i] == '"' && input[var->i + 1] == '"')
	{
		var->str = ft_strdup("");
		var->i += 2;
		var->j = 1;
	}
	else
	{
		var->i++;
		var->j = 0;
		while (input[var->i] && input[var->i] != '"')
		{
			var->j++;
			var->i++;
		}
		if (!input[var->i])
			return (printf("double quotes not closed\n"), 0);
		else
		{
			var->str = ft_substr(input, var->i - var->j, var->j);
			var->limiter = ft_strjoin(var->limiter, var->str);
		}
		var->i++;
	}
	return (1);
}

int	ft_tok_input_h_ut2(char *input, t_data *var)
{
	if (input[var->i] == '"' && input[var->i + 1] == '"')
	{
		var->str = ft_strdup("");
		var->i += 2;
		var->j = 1;
	}
	else
	{
		var->i++;
		var->j = 0;
		while (input[var->i] && input[var->i] != '\'')
		{
			var->j++;
			var->i++;
		}
		if (!input[var->i])
			return (printf("single quotes not closed\n"), 0);
		else
		{
			var->str = ft_substr(input, var->i - var->j, var->j);
			var->limiter = ft_strjoin(var->limiter, var->str);
		}
		var->i++;
	}
	return (1);
}

void	ft_tok_input_h_ut3(char *input, t_data *var)
{
	var->j = 0;
	while (input[var->i] && input[var->i] != '\''
		&& input[var->i] != '"' && input[var->i] != ' '
		&& input[var->i] != '<' && input[var->i] != '>'
		&& input[var->i] != '|')
	{
		var->j++;
		var->i++;
	}
	var->str = ft_substr(input, var->i - var->j, var->j);
	var->limiter = ft_strjoin(var->limiter, var->str);
}

int	ft_tok_input_h(t_list **node, char *input, t_data *var)
{
	var->limiter = NULL;
	var->str = NULL;
	var->i += 2;
	ft_lstadd_back(node, ft_lstnew(ft_strdup("<<"), INPUT_H));
	while (input[var->i] == ' ')
		var->i++;
	while (input[var->i] && input[var->i] != ' ' && input[var->i] != '<'
		&& input[var->i] != '>' && input[var->i] != '|')
	{
		if (input[var->i] == '"')
		{
			if (!ft_tok_input_h_ut1(input, var))
				return (free(var->limiter), 0);
		}
		else if (input[var->i] == '\'')
		{
			if (!ft_tok_input_h_ut2(input, var))
				return (free(var->limiter), 0);
		}
		else
			ft_tok_input_h_ut3(input, var);
		free(var->str);
	}
	ft_lstadd_back(node, ft_lstnew(var->limiter, LIMITER));
	return (var->j = 3, 1);
}
