/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:55:58 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 17:51:47 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	is_digit(char *str)
{
	int	i;

	i = 1;
	if ((str[0] != '-' && str[0] != '+' && !ft_isdigit(str[0])))
	{
		return (1);
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	choose_exit_code(t_main *tools, t_cmd *simple_cmd)
{
	int	exit_code;

	(void)simple_cmd;
	(void)tools;
	if (!simple_cmd->cmd_args[1])
		exit_code = 0;
	else if (is_digit(simple_cmd->cmd_args[1]) == 0)
		exit_code = ft_atoi(simple_cmd->cmd_args[1]);
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(simple_cmd->cmd_args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 255;
	}
	free_all(tools);
	exit(exit_code);
	return (0);
}

int	my_exit(t_main *tools, t_cmd *simple_cmd)
{
	ft_putendl_fd("exit", 2);
	if (simple_cmd->cmd_args[1] && simple_cmd->cmd_args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (tools->sh_lvl > 1)
		tools->sh_lvl--;
	choose_exit_code(tools, simple_cmd);
	return (0);
}
