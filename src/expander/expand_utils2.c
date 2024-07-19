/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:59:34 by rheck             #+#    #+#             */
/*   Updated: 2024/03/06 11:57:21 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	*replace_pid(char *input, char *old, char *new, t_main *db)
{
	free(old);
	free(new);
	return (replace_string(input, ft_strdup("$$"),
			ft_itoa((int)getpid()), db));
}

void	expand_var(t_main *db)
{
	int		i;
	char	*error_value;

	i = -1;
	while (db->token_arr[++i] && db->token_arr[i]->type != EOF_TOKEN)
	{
		if (db->token_arr[i]->type != STRING)
		{
			while (is_dollar(db->token_arr[i]->value) != -1)
			{
				if (db->token_arr[i]->value
					[first(db->token_arr[i]->value)] == '?')
				{
					error_value = ft_itoa(g_g.l_e_c);
					db->token_arr[i]->value = replace_string
						(db->token_arr[i]->value, ft_strdup("$?"), 
							error_value, db);
					free(error_value);
				}
				else if (db->token_arr[i - 1]
					&& ft_strncmp(db->token_arr[i - 1]->value, "<<", 2))
					expend(&(db->token_arr[i]->value), db->env_tab, db);
			}
		}
	}
}
