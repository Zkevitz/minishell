/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_id_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:18:46 by rheck             #+#    #+#             */
/*   Updated: 2024/03/01 10:57:02 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	*add_quotes(char *input, char quote_type, t_main *db)
{
	int		len;
	char	*quoted_str;

	len = ft_strlen(input);
	quoted_str = (char *)malloc(len + 3);
	if (!quoted_str)
		exit_free(db, 1);
	quoted_str[0] = quote_type;
	ft_strcpy(quoted_str + 1, input);
	quoted_str[len + 1] = quote_type;
	quoted_str[len + 2] = '\0';
	free(input);
	return (quoted_str);
}

char	*read_q_s(char *input, char *old, t_main *db)
{
	int		closing_quote_pos;
	int		q_s_lgth;
	char	*q_str;
	char	q_t;

	q_t = wq(input);
	if (q_t == '\0')
		expend(&input, db->env_tab, db);
	if (q_t == '\0')
		return (input);
	closing_quote_pos = f_q(input, q_t, f_q(input, q_t, 0) + 1);
	q_s_lgth = closing_quote_pos - f_q(input, q_t, 0);
	q_str = malloc(q_s_lgth + 1);
	if (!q_str)
		exit_free(db, 1);
	ft_strncpy(q_str, input + f_q(input, q_t, 0) + 1, q_s_lgth - 1);
	q_str[q_s_lgth - 1] = '\0';
	if (is_dollar(input) == -1 || q_t == '\'')
		input = replace_string(input, add_quotes(old, q_t, db), q_str, db);
	if (is_dollar(input) == -1 || q_t == '\'')
		return (input);
	expand_for_quotes(&q_str, db->env_tab, db);
	replace_string(input, add_quotes(old, q_t, db), q_str, db);
	free(q_str);
	return (input);
}
