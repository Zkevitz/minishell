/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:35 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 16:58:18 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	*read_option(t_Lexer *lexer, t_main *db)
{
	int		start_pos;
	int		option_length;
	char	*option;

	start_pos = lexer->pos;
	while (ft_isalpha(lexer->input[lexer->pos]) || 
		lexer->input[lexer->pos] == '-')
		lexer->pos++;
	option_length = lexer->pos - start_pos;
	option = malloc(option_length + 1);
	if (!option)
		exit_free(db, 1);
	ft_strncpy(option, lexer->input + start_pos, option_length);
	option[option_length] = '\0';
	return (option);
}
