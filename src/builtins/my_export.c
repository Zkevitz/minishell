/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:56:21 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 17:51:57 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	variable_exist(t_main *tools, char *str)
{
	int	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
	while (tools->env_tab[i])
	{
		if (ft_strncmp(tools->env_tab[i],
				str, equal_sign(tools->env_tab[i])) == 0)
		{
			free(tools->env_tab[i]);
			tools->env_tab[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	if (str[equal_sign(str)] == '\"')
		delete_quotes(str, '\"');
	if (str[equal_sign(str)] == '\'')
		delete_quotes(str, '\'');
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

int	check_parameter(char *str, t_main *data_base)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (ft_isdigit(str[0]))
		return (export_error(str));
	if (equal_sign(str) == 0)
		return (1);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
		{
			if (data_base->export_error == 0)
				return (export_error(str));
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	my_export(t_main *tools, t_cmd *simple_cmd)
{
	char	**tmp;
	int		i;
	int		exit_code;

	i = 0;
	if (!simple_cmd->cmd_args[1] || simple_cmd->cmd_args[1][0] == '\0')
		return (my_env(tools, simple_cmd));
	exit_code = check_arg(simple_cmd->cmd_args, tools);
	while (simple_cmd->cmd_args[++i])
	{
		if (check_parameter(simple_cmd->cmd_args[i], tools) == 0
			&& variable_exist(tools, simple_cmd->cmd_args[i]) == 0)
		{
			if (simple_cmd->cmd_args[i])
			{
				tmp = add_var(tools->env_tab, simple_cmd->cmd_args[i]);
				free_arr(tools->env_tab);
				tools->env_tab = ft_arraydup(tmp);
				return (0);
			}
		}
	}
	return (exit_code);
}
