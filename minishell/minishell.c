/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/22 10:49:07 by asabbar          ###   ########.fr       */
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

void	run_minishell(t_cd	*cd, int fd_his)
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
		{
			ft_putstr_fd(input, fd_his);
			ft_putstr_fd("\n", fd_his);
			add_history(input);
		}
		free(input);
	}
}

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
	input = NULL;
	fd_his = 0;
	signal(SIGINT, &handle_sigs);
	signal(SIGQUIT, &handle_sigs);
	rl_catch_signals = 0;
	if (ac != 1)
		return (printf("error in argm\n"), 0);
	cd = malloc(sizeof(t_cd));
	ft_new_env(env, cd);
	g_ds = 0;
	fd_his = add_hist(fd_his);
	run_minishell(cd, fd_his);
	write(1, "\033[1A\033[14Cexit\n", 15);
	ft_fre(cd->my_env);
	free(cd->pwd);
	free(cd);
	return (0);
}
