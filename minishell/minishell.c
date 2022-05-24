/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/24 01:49:48 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void red () {
  printf("\033[1;31m");
}

char **ft_new_env(char **env,char **my_env)
{
	int i = 0;
	char *tmp;
	
	{
		while(env[i])
			i++;
		my_env = malloc(sizeof(char *) * i + 1);
		i = -1;
		while(env[++i])
			my_env[i] = ft_strdup(env[i]);
		my_env[i] = NULL;
	}
	return(my_env);
}

int main(int ac, char **av, char **env)
{
	char	*input;
	char	**my_env;

	(void)av;
	if(ac != 1)
		return (printf("error in argm\n"),0);
	my_env = ft_new_env(env,my_env);
	input = NULL;
	while (1)
	{
		red ();
		input = readline("➜ \033[0;32m minishell \033[0;37m: ");
		if(!input || !ft_strcmp(input, "exit"))
			break ;
		ft_parser(input, my_env);
		if(input[0] != '\0')
			add_history(input);
		free(input);
	}
	printf("exit\n");
	return 0;
}