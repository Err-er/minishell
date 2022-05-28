/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:57 by zait-sli          #+#    #+#             */
/*   Updated: 2022/05/28 05:22:09 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_dup_env(t_cd *cd)
{
	int i = 0;

	while(cd->my_env[i])
		i++;
	cd->sorted = malloc(sizeof(char *) * (i+1));
	i = 0;
	while(cd->my_env[i])
	{
		cd->sorted[i] = ft_strdup(cd->my_env[i]);
		i++;
	}
	cd->sorted[i] = NULL;
}

void ft_sort_expo(t_cd *cd)
{
	int i = 0;
	int j = 0;
	char *temp;

	ft_dup_env(cd);
	while(cd->sorted[i])
	{
		j = 0;
		while(cd->sorted[j])
		{
			if (cd->sorted[i][0] < cd->sorted[j][0])
			{
				temp = cd->sorted[i];
				cd->sorted[i] = cd->sorted[j];
				cd->sorted[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_export(t_cd *cd)
{
	int i = 0;

	while(cd->sorted[i])
	{
		printf("declare -x %s\n",cd->sorted[i]);
		i++;
	}
}

void	export_this(t_cd *cd, char *s)
{
	char **new_env;
	int i= 0;

	while(cd->my_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while(cd->my_env[i])
	{
		new_env[i] = ft_strdup(cd->my_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(s);
	i++;
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
	t = ft_strjoin(t,"=\"");
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
	char **t;

	// if (!ft_strchr(s,'='))
	// 	return(0);
	
	while(env[i])
	{
		if (!ft_strcmp(s, env[i]))
			return(0);
		i++;
	}
	i = 0;
	t = ft_split_2(s,'=');
	while(t[0][i])
	{
		if ((t[0][i] < 65  && t[0][i] != 43 && t[0][i] != 61 && t[0][i] != 32)|| t[0][i] > 122 || (t[0][i] >= 91 && t[0][i] <=94) || t[0][i] == 96)
		{
			printf("minishell: export: `%s': not a valid identifier\n",s);
			return(0);
		}
		i++;
	}
	ft_fre(t);
	return(1);
}

void	ft_exprot(t_list **node, t_cd *cd)
{
	t_list *head;

	head = *node;
	head = head->next;
	ft_sort_expo(cd);
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
			if (check_valid(head->next->data,cd->my_env) && !check_exist(head->next->data,cd->my_env ) && head->next->tokn != WS)
				export_this(cd, head->next->data);
			else if (check_valid(head->next->data,cd->my_env) && check_exist(head->next->data,cd->my_env) && head->next->tokn != WS)
				replace_this(cd, head->next->data);
			head = head->next;
		}
	}
}