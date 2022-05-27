/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:57 by zait-sli          #+#    #+#             */
/*   Updated: 2022/05/27 16:38:01 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_cd *cd)
{
	int i = 0;

	while(cd->my_env[i])
	{
		printf("declare -x ");
		printf("%s\n",cd->my_env[i]);
		i++;
	}
}

void	export_this(t_cd *cd, char *s)
{
	char **new_env;
	int i;

	cd->env_len++;
	new_env = malloc(sizeof(char *) * cd->env_len);
	i = -1;
	while(cd->my_env[++i])
		new_env[i] = ft_strdup(cd->my_env[i]);
	new_env[i++] = ft_strdup(s);
	new_env[i] = NULL;
	free(cd->my_env);
	cd->my_env = new_env;
}

char *ft_cpoy_content(char *s, char *f)
{
	int i = 0;
	char *t;

	t = ft_strdup(f);
	while(s[i] != '=')
		i++;
	i++;
	t = ft_strjoin(t,"=");
	t = ft_strjoin(t,"\"");
	t = ft_strjoin(t,&s[i]);
	t = ft_strjoin(t,"\"");
	return(t);
}

void	replace_this(t_cd *cd, char *s)
{
	int i = 0;
	char *temp;
	char **t;
	char **t1;
	
	t1 = ft_split_2(s,'=');
	while(cd->my_env[i])
	{
		t = ft_split_2(cd->my_env[i],'=');
		if (t[0] && t1[0] && !ft_strcmp(t[0],t1[0]))
		{
			temp = ft_cpoy_content(s,t1[0]);
			cd->my_env[i] = temp;
			ft_fre(t);
			ft_fre(t1);
			return ;
		}
		ft_fre(t);
		i++;
	}
	
}

int check_exist(char *s,char **env)
{
	int i = 0;
	char **t;
	char **t1;
	
	t1 = ft_split_2(s,'=');
	while(env[i])
	{
		t = ft_split_2(env[i],'=');
		if (t[0] && t1[0] && !ft_strcmp(t[0],t1[0]))
		{
			ft_fre(t);
			ft_fre(t1);
			return(1);
		}
		ft_fre(t);
		i++;
	}
	ft_fre(t1);
	return(0);
}

int	check_valid(char *s,char **env)
{
	int i = 0;
	char *temp;

	if (!ft_strchr(s,'='))
		return(0);
	while(env[i])
	{
		if (!ft_strcmp(s, env[i]))
			return(0);
		i++;
	}
	return(1);
}

void	ft_exprot(t_list **node, t_cd *cd)
{
	t_list *head;

	head = *node;
	head = head->next;
	while(1)
	{
		if (head->next->tokn == WS)
			head = head->next;
		else
			break  ;
	}
	if (head->next->tokn == END_TOKN || head->next->tokn == ST_TOKN)
	{
		ft_print_export(cd);
		return ;
	}
	else if (head->next->tokn == Oredi || head->next->tokn == Iredi || head->next->tokn == output_h || head->next->tokn == input_h)
	{
		ft_print_export(cd);
		return ;
	}
	else
	{
		while(head->next->tokn != END_TOKN || head->next->tokn != ST_TOKN)
		{
			if (check_valid(head->next->data,cd->my_env) && !check_exist(head->next->data,cd->my_env))
				export_this(cd, head->next->data);
			else if (check_valid(head->next->data,cd->my_env) && check_exist(head->next->data,cd->my_env))
				replace_this(cd, head->next->data);
			head = head->next;
		}
	}
}