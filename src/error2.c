/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:16:15 by rheck             #+#    #+#             */
/*   Updated: 2024/03/01 12:23:36 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	cmd_not_found(char *str)
{
	struct stat	path_stat;

	if (stat(str, &path_stat) == 0 && (ft_strncmp(str, "/", 1) == 0
			||ft_strncmp(str, "./", 2) == 0)) 
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("bash : ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (126);
		}
	}
	if (access(str, F_OK) == 0 && access(str, X_OK)
		< 0 && access(str, R_OK) < 0)
	{
		permission_error(str);
		return (126);
	}
	if (ft_strncmp(str, "/", 1) == 0 || ft_strncmp(str, "./", 2) == 0)
		return (path_not_found(str));
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

void	permission_error(char *str)
{
	ft_putstr_fd("bash: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}
