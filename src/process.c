/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:32:46 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 16:15:19 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

void	process(t_main *data_base)
{
	int		i;
	t_Lexer	lexer;

	i = 0;
	data_base->token_arr = malloc(sizeof(t_Token *)
			* (count_token(&lexer, data_base->my_prompt_line, data_base) + 1));
	if (!data_base->token_arr)
	{
		exit_free(data_base, 1);
	}
	init_lexer(&lexer, data_base->my_prompt_line);
	data_base->token_arr[i] = get_next_token(&lexer, data_base);
	while (data_base->token_arr[i]->type != 5)
	{
		data_base->token_arr[++i] = get_next_token(&lexer, data_base);
	}
	return ;
}
