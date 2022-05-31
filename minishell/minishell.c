/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/05/31 06:22:03 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int ds = 0;

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
}

void handle_sigs(int sig)
{
	// printf("\n");
}

int main(int ac, char **av, char **env)
{
	char	*input;
	t_cd *cd;
	struct sigaction sa;
	sa.sa_handler = &handle_sigs;
	sa.sa_flags = SA_RESTART;
	sa.sa_mask = SIGQUIT;
	sigaction(SIGINT,&sa, NULL);


	(void)av;
	if(ac != 1)
		return (printf("error in argm\n"),0);
	cd = malloc(sizeof(t_cd));
	ft_new_env(env,cd);
	input = NULL;
	ds = 0;
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