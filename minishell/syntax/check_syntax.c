/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:33:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/13 10:47:10 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	print_error(void)
{
	ft_putstr_fd("syntax error \n", 2);
}

int	ft_check_syntax(t_list	*node, char *input)
{
	t_list	*head;
	int		i;
	int		j;

	j = 0;
	while (j < 4)
	{
		if (j == 0)
		{
			i = 0;
			while (input[i] == ' ' && input[i])
				i++;
		}
		if (j == 1)
		{
			i = 0;
			while (input[i] != '<' && input[i])
				i++;
		}
		if (j == 2)
		{
			i = 0;
			while (input[i] != '>' && input[i])
				i++;
		}
		if (j == 3)
		{
			i = 0;
			while (input[i] != '|' && input[i])
				i++;
		}
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i])
				return (print_error(), 0);
			else
				return (1);
		}
		if (input[i] == '<')
		{
			i++;
			while (input[i] && input[i] == ' '
				&& input[i] != '|' && input[i] != '<' && input[i] != '>')
				i++;
			if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error(), 0);
			else
				return (1);
		}
		if (input[i] == '>' && input[i + 1] == '>')
		{
			i += 2;
			while (input[i] && input[i] == ' '
				&& input[i] != '|' && input[i] != '<' && input[i] != '>')
				i++;
			if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error(), 0);
			else
				return (1);
		}
		if (input[i] == '>')
		{
			i++;
			while (input[i] && input[i] == ' '
				&& input[i] != '|' && input[i] != '<' && input[i] != '>')
				i++;
			if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error(), 0);
			else
				return (1);
		}
		if (input[i] == '|')
		{
			i++;
			while (input[i] && input[i] == ' '
				&& input[i] != '|' && input[i] != '<' && input[i] != '>')
				i++;
			if (!input[i] || input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error(), 0);
			else
				return (1);
		}
		j++;
	}
	return (1);
}
