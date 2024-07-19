/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:17 by rheck             #+#    #+#             */
/*   Updated: 2024/03/01 12:00:14 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	check_arg(char **tab, t_main *data_base)
{
	int	i;

	i = 0;
	if (tab[1][0] == '=')
		return (1);
	if (ft_isdigit(tab[1][0]))
		return (1);
	while (tab[1][i] != '\0')
	{
		if (tab[1][i] == '=')
			break ;
		if (check_valid_identifier(tab[1][i]))
		{
			data_base->export_error = 1;
			export_error(tab[1]);
			return (1);
		}
		i++;
	}
	if (equal_sign(tab[1]) == 0 && !tab[2])
		return (0);
	return (0);
}
