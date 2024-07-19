/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:55:42 by rheck             #+#    #+#             */
/*   Updated: 2024/03/01 12:00:22 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	my_env(t_main *data_base, t_cmd *simple_cmd)
{
	int	i;

	(void)simple_cmd;
	i = 0;
	while (data_base->env_tab[i] != NULL)
	{
		ft_putendl_fd(data_base->env_tab[i], 1);
		i++;
	}
	return (0);
}
