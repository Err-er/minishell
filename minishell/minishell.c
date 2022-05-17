/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/17 10:05:51 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char	*input;
	// char	**cmds;
	// int		pid;

	(void)av;
	if(ac != 1)
		return (printf("error in argm\n"),0);
	input = NULL;
	while (!input || ft_strcmp(input, "exit"))
	{
		input = readline("minishell -> ");
		if(!input)
			break ;
		ft_parser(input, env);
		free(input);
	}
	printf("exit\n");
	return 0;
}