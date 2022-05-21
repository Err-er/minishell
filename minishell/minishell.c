/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/21 12:05:41 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char	*input;
	// char	**cmds;
	int		pid;

	(void)av;
	if(ac != 1)
		return (printf("error in argm\n"),0);
	input = NULL;
	while (1)
	{
		input = readline("minishell -> ");
		if(!input || !ft_strcmp(input, "exit"))
			break ;
		pid = fork();
		if (pid == 0)
		{
			ft_parser(input, env);
			exit(0);
		}
		if(input[0] != '\0')
			add_history(input);
		waitpid(pid, NULL, 0);
		free(input);
	}
	printf("exit\n");
	return 0;
}