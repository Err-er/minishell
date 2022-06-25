/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/24 20:32:39 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	g_ds = 0;

int	get_global3(int i)
{
	static int	j;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 1;
	else
		return (j);
	return (j);
}

void	run_minishell(t_cd	*cd)
{
	char	*input;

	while (1)
	{
		get_global(0);
		get_global3(1);
		input = readline("➜ minishell $ ");
		if (!input)
			break ;
		ft_parser(input, cd);
		if (input[0])
			add_history(input);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cd	*cd;

	(void)av;
	input = NULL;
	signal(SIGINT, &handle_sigs);
	signal(SIGQUIT, &handle_sigs);
	rl_catch_signals = 0;
	if (ac != 1)
		return (printf("error in argm\n"), 0);
	cd = malloc(sizeof(t_cd));
	ft_new_env(env, cd);
	g_ds = 0;
	run_minishell(cd);
	write(1, "\033[1A\033[14Cexit\n", 15);
	ft_fre(cd->my_env);
	free(cd->pwd);
	free(cd);
	return (0);
}
