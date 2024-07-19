/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:32 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 16:57:16 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

char	*read_operator(t_Lexer *lexer, t_main *db)
{
	size_t	start_pos;
	size_t	operator_length;
	char	*operator_str;

	start_pos = lexer->pos;
	while (is_operator_char(lexer->input[lexer->pos]))
		lexer->pos++;
	operator_length = lexer->pos - start_pos;
	operator_str = malloc(operator_length + 1);
	if (!operator_str)
		exit_free(db, 1);
	ft_strncpy(operator_str, lexer->input + start_pos, operator_length);
	operator_str[operator_length] = '\0';
	return (operator_str);
}
