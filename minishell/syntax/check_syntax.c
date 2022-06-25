/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:33:35 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/23 20:35:40 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_check_oredi(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] != '>')
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i]
				|| input[i] == '|' || input[i] == '<' || input[i] == '>')
				return (print_error_syntax(), 0);
		}
		i++;
	}
	return (1);
}

int	ft_check_syntax(char *input)
{
	if (!ft_check_pipe(input))
		return (0);
	if (!ft_check_input_h(input))
		return (0);
	if (!ft_check_iredi(input))
		return (0);
	if (!ft_check_output_h(input))
		return (0);
	if (!ft_check_oredi(input))
		return (0);
	return (1);
}
