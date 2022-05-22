/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/21 17:34:10 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void red () {
  printf("\033[1;31m");
}

int main(int ac, char **av, char **env)
{
	char	*input;
	int		pid;

	(void)av;
	if(ac != 1)
		return (printf("error in argm\n"),0);
	input = NULL;
	while (1)
	{
		red ();
		input = readline("➜ \033[0;32m minishell : \033[0;37m");
		if(!input || !ft_strcmp(input, "exit"))
			break ;
		ft_parser(input, env);
		if(input[0] != '\0')
			add_history(input);
		waitpid(pid, NULL, 0);
		free(input);
	}
	printf("exit\n");
	return 0;
}