/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 06:46:31 by zait-sli          #+#    #+#             */
/*   Updated: 2022/06/10 05:20:22 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(char **env)
{
	int	i;
	int j;
	char *s;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strchr(env[i],'='))
		{
			if (ft_strchr(env[i],'"'))
			{
				s = ft_strchr(env[i],'=');
				printf("%s",ft_substr(env[i],0, ft_strlen(env[i]) - (ft_strlen(s) - 1)));
				s = ft_strtrim(&s[2],"\"");
				printf("=");
				printf("%s\n",s);
				free(s);
			}
			else
				printf("%s\n",env[i]);
		}
		i++;
	}
}

void increase_shelvl(t_cd *cd)
{
	char *temp;

	cd->shlvl += 1;
	if (get_path(cd->my_env,"SHLVL"))
	{
		temp = ft_strdup("SHLVL=");
		temp = ft_strjoin(temp,ft_itoa(cd->shlvl));
		replace_this(cd,temp);
		// write(2,temp, ft_strlen(temp));	
	}
}
