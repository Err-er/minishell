/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:40:32 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/23 20:37:54 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_nul_cm(char *str)
{
	char	**s;

	s = ft_split_2(str, '\v');
	if (!s[0])
		return (ft_fre(s), 1);
	return (ft_fre(s), 0);
}

int	ft_inputh_p(t_vars *var, t_list	**head, char *str)
{
	char	*p;

	var->value = NULL;
	(*head) = (*head)->next;
	while ((*head)->tokn == WS && (*head)->tokn != END_TOKN)
		(*head) = (*head)->next;
	dup2(var->st_in, 0);
	while (1)
	{
		p = readline("> ");
		if (!ft_strcmp2(p, (*head)->data))
		{
			free(p);
			break ;
		}
		p = ft_strjoin(p, "\n");
		var->value = ft_strjoin(var->value, p);
		free(p);
	}
	var->br = ft_check_nul_cm(str);
	return (1);
}

int	ft_iredi_p(t_vars *var, t_list	**head, char *str)
{
	var->file_n = ft_strdup("");
	(*head) = (*head)->next;
	if ((*head)->tokn == WS)
		(*head) = (*head)->next;
	while ((*head)->tokn == WR && (*head)->tokn != END_TOKN)
	{
		var->file_n = ft_strjoin(var->file_n, (*head)->data);
		(*head) = (*head)->next;
	}
	var->fd[0] = open(var->file_n, O_RDWR, 0677);
	if (var->fd[0] == -1 || !var->file_n)
	{
		perror("Error");
		var->br = 1;
		free(var->file_n);
		return (0);
	}
	var->br = ft_check_nul_cm(str);
	free(var->file_n);
	var->x[0] = 0;
	return (1);
}

void	ft_check_redi_p(t_vars *var, char *str, t_list *head)
{
	while (head && head->tokn != PIPE)
	{
		if (head->tokn == OREDI)
		{
			if (!ft_oredi_p(var, &head, str))
				break ;
		}
		else if (head->tokn == OUTPUT_H)
		{
			if (!ft_outputh_p(var, &head, str))
				break ;
		}
		else if (head->tokn == INPUT_H)
		{
			if (!ft_inputh_p(var, &head, str))
				break ;
		}
		else if (head->tokn == IREDI)
		{
			if (!ft_iredi_p(var, &head, str))
				break ;
		}
		else
			head = head->next;
	}
}

void	inisial(t_vars	*var, char **str)
{
	var->br = 0;
	var->c = 0;
	var->c2 = 0;
	var->i = 0;
	var->file_n = ft_strdup("");
	var->value = NULL;
	while (str[var->i])
		var->i++;
	var->id = malloc(var->i * sizeof(int));
	var->i = -1;
	var->st_in = dup(0);
	var->st_out = dup(1);
	var->str = str;
}
