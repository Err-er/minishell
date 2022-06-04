/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:50:59 by asabbar           #+#    #+#             */
/*   Updated: 2022/06/04 14:00:06 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	ds = 0;

void	ft_new_env(char **env, t_cd *cd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
		i++;
	cd->my_env = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (env[++i])
		cd->my_env[i] = ft_strdup(env[i]);
	cd->my_env[i] = NULL;
	if (get_path(cd->my_env, "OLDPWD"))
		unset_this(cd, "OLDPWD");
	cd->pwd = ft_strdup("PWD=");
	cd->pwd = ft_strjoin(cd->pwd, get_path(cd->my_env, "PWD"));
}

void	handle_sigs(int sig)
{
	if (sig == SIGINT && !get_global(15))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		printf("\n");
}

int	get_global(int i)
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

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cd	*cd;

	(void)av;
	signal(SIGINT, &handle_sigs);
	signal(SIGQUIT, &handle_sigs);
	rl_catch_signals = 0;
	if (ac != 1)
		return (printf("error in argm\n"), 0);
	cd = malloc(sizeof(t_cd));
	ft_new_env(env, cd);
	input = NULL;
	ds = 0;
	while (1)
	{
		get_global(0);
		input = readline("➜ minishell $ ");
		if (!input)
			break ;
		ft_parser(input, cd);
		if (input)
			add_history(input);
		free(input);
	}
	write(1, "\033[1A\033[14Cexit\n", 15);
	return (0);
}
