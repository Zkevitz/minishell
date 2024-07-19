/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:00:37 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 16:53:26 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	*read_number(t_Lexer *lexer, t_main *db)
{
	int		start_pos;
	int		number_length;
	char	*number;

	start_pos = lexer->pos;
	while (ft_isdigit(lexer->input[lexer->pos]))
		lexer->pos++;
	number_length = lexer->pos - start_pos;
	number = malloc(number_length + 1);
	if (!number)
		exit_free(db, 1);
	ft_strncpy(number, lexer->input + start_pos, number_length);
	number[number_length] = '\0';
	return (number);
}
