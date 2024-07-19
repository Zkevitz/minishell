/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:55:28 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 18:23:53 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	change_path(t_main *tools)
{
	char	*tmp;

	tmp = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = tmp;
	change_env_tab(tools->old_pwd, tools, "OLDPWD=");
	if (getcwd(NULL, sizeof(NULL)))
	{
		free(tools->pwd);
		tools->pwd = getcwd(NULL, sizeof(NULL));
	}
	else
	{
		chdir("..");
		change_path(tools);
	}
	change_env_tab(tools->pwd, tools, "PWD=");
	return (0);
}

void	change_env_tab(char *new_pos, t_main *tools, const char *to_find)
{
	int		i;
	int		tab_len;
	char	*str;

	i = 0;
	tab_len = 0;
	while (tools->env_tab[i])
	{
		tab_len++;
		i++;
	}
	i = 0;
	while (tools->env_tab[i] 
		&& ft_strncmp(tools->env_tab[i], to_find, ft_strlen(to_find)) != 0)
	{
		i++;
	}
	if (tab_len > i)
	{
		free(tools->env_tab[i]);
		str = ft_strjoin(to_find, new_pos);
		tools->env_tab[i] = str;
	}
	return ;
}

int	specific_path(t_main *tools, char *str)
{
	char	*tmp;
	int		ret;

	(void)tools;
	tmp = fev(tools->env_tab, str);
	ret = chdir(tmp);
	if (ret != 0)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" not set\n", 2);
	}
	free(tmp);
	return (ret);
}

int	back_on_path(t_main *tools, t_cmd *simple_cmd)
{
	char	*tmp;
	int		ret;
	int		i;

	(void)simple_cmd;
	i = ft_strlen(tools->pwd);
	while (tools->pwd[i] != '/')
		i--;
	tmp = malloc(sizeof(char) * i + 1);
	if (!tmp)
		exit_free(tools, 1);
	ft_memcpy(tmp, tools->pwd, i);
	tmp[i] = '\0';
	ret = chdir(tmp);
	free(tmp);
	return (ret);
}

int	my_cd(t_main *tools, t_cmd *simple_cmd)
{
	if (!simple_cmd->cmd_args[1])
	{
		specific_path(tools, "HOME");
	}
	else if (!ft_strncmp(simple_cmd->cmd_args[1], "..", 2) 
		&& simple_cmd->cmd_args[1][2] == '\0')
	{
		back_on_path(tools, simple_cmd);
	}
	else
	{
		if ((chdir(simple_cmd->cmd_args[1])))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(simple_cmd->cmd_args[1], 2);
			perror(" ");
			return (1);
		}
	}
	change_path(tools);
	return (0);
}
