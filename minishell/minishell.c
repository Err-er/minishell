/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/28 16:36:09 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_new_env(char **env,t_cd *cd)
{
	int i = 0;
	char *tmp;
	
	{
		while(env[i])
			i++;
		cd->my_env = malloc(sizeof(char *) * i + 1);
		i = -1;
		while(env[++i])
			cd->my_env[i] = ft_strdup(env[i]);
		cd->my_env[i] = NULL;
	}
	cd->env_len = i;
	// return(my_env);
}

int main(int ac, char **av, char **env)
{
	char	*input;
	// char	**my_env;
	t_cd *cd;

	(void)av;
	//rl_catch_signals = 0;
	if(ac != 1)
		return (printf("error in argm\n"),0);
	cd = malloc(sizeof(t_cd));
	ft_new_env(env,cd);
	input = NULL;
	while (1)
	{
		input = readline("➜ minishell $ ");
		if(!input || !ft_strcmp(input, "exit"))
			break ;
		ft_parser(input, cd);
		if(input)
			add_history(input);
		free(input);
	}
	printf("exit\n");
	return 0;
}