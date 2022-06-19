/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/19 16:57:12 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	ds = 0;

int	add_hist(int fd_his)
{
	char	*input;

	fd_his = open(HISTORY_COM, O_CREAT | O_RDWR, O_APPEND, 0666);
	input = get_next_line(fd_his);
	while (input)
	{
		input = ft_strtrim2(input, "\n");
		add_history(input);
		free(input);
		input = get_next_line(fd_his);
	}
	free(input);
	return (fd_his);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cd	*cd;
	int		fd_his;

	(void)av;
	signal(SIGINT, &handle_sigs);
	signal(SIGQUIT, &handle_sigs);
	rl_catch_signals = 0;
	if (ac != 1)
		return (printf("error in argm\n"), 0);
	cd = malloc(sizeof(t_cd));
	ft_new_env(env, cd);
	ds = 0;
	fd_his = add_hist(fd_his);
	run_minishell(cd, fd_his);
	write(1, "\033[1A\033[14Cexit\n", 15);
	ft_fre(cd->my_env);
	free(cd->pwd);
	free(cd);
	return (0);
}
