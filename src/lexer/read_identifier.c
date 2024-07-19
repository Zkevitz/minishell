/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:52:45 by rheck             #+#    #+#             */
/*   Updated: 2024/03/06 11:13:02 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	wq(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] != '\'' && input[i] != '\"'))
		i++;
	return (input[i]);
}

int	f_q(char *input, char quote_type, int index)
{
	if (quote_type == '\0')
		return (0);
	while (input[index] != '\0' && input[index] != quote_type)
		index++;
	return (index);
}

int	i_s_v_c(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '/' || c == '.'
		|| c == '=' || c == '$' || c == '?' || c == '-' || c == '+'
		|| c == '\'' || c == '\"' || c == '^' || c == '%' );
}

char	*copy(char *input, t_main *db)
{
	int		start_pos;
	int		closing_quote_pos;
	int		quoted_string_length;
	char	*quoted_string;
	char	quote_type;

	quote_type = wq(input);
	if (quote_type == '\0')
		return (input);
	start_pos = f_q(input, quote_type, 0);
	closing_quote_pos = f_q(input, quote_type, start_pos + 1);
	quoted_string_length = closing_quote_pos - start_pos;
	quoted_string = malloc(quoted_string_length + 1);
	if (!quoted_string)
		exit_free(db, 1);
	ft_strncpy(quoted_string, input + start_pos + 1, quoted_string_length - 1);
	quoted_string[quoted_string_length - 1] = '\0';
	return (quoted_string);
}

char	*read_id(t_Lexer *lex, t_main *db)
{
	int		start_pos;
	char	*id;

	start_pos = lex->pos;
	if (!i_s_v_c(lex->input[start_pos]) && 
		lex->input[start_pos] != '_')
		return (NULL);
	while (i_s_v_c(lex->input[lex->pos])
		|| (lex->in_cmd == 2 && lex->input[lex->pos] == ' '))
	{
		if (lex->input[lex->pos] == '\"' || lex->input[lex->pos] == '\'')
			lex->in_cmd = 2;
		lex->pos++;
		if ((lex->input[lex->pos] == '\"'
				|| lex->input[lex->pos] == '\'') && lex->in_cmd == 2)
			lex->in_cmd = -1;
	}
	id = malloc((lex->pos - start_pos) + 1);
	if (!id)
		exit_free(db, 1);
	ft_strncpy(id, lex->input + start_pos, lex->pos - start_pos);
	id[lex->pos - start_pos] = '\0';
	id = read_q_s(id, copy(id, db), db);
	return (id);
}
