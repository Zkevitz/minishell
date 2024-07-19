/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:17:58 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 18:23:53 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

void	init_lexer(t_Lexer *lexer, const char *input)
{
	lexer->pos = 0;
	lexer->is_cmd = 1;
	lexer->in_cmd = -1;
	lexer->input = input;
}

void	skip_whitespace(t_Lexer *lexer, char **value)
{
	*value = NULL;
	if (!lexer->input)
		return ;
	while (lexer->pos < ft_strlen(lexer->input)
		&& is_space(lexer->input[lexer->pos]))
		lexer->pos++;
}

t_Token	*create_token(t_TokenType type, char *value, t_main *db)
{
	t_Token	*token;

	token = malloc(sizeof(t_Token) * 1);
	if (!token)
		exit_free(db, 1);
	if (value == NULL && type != EOF_TOKEN)
	{
		token->type = DONE;
		token->value = value;
		return (token);
	}
	token->type = type;
	token->value = value;
	return (token);
}

t_Token	*try_last_token(t_Lexer *lexer, char current_char,
	char *value, t_main *db)
{
	if (ft_isdigit(current_char))
	{
		value = read_number(lexer, db);
		return (create_token(NUMBER, value, db));
	}
	if (current_char == '-')
	{
		value = read_option(lexer, db);
		return (create_token(OPTION, value, db));
	}
	else if (current_char == '|' || current_char == '>' || current_char == '<')
	{
		value = read_operator(lexer, db);
		if (ft_strncmp(value, "|", 1) == 0)
		{
			lexer->is_cmd = 1;
			return (create_token(PIPE, value, db));
		}
		return (create_token(OPERATOR, value, db));
	}
	else
		return (create_token(EOF_TOKEN, NULL, db));
}

t_Token	*get_next_token(t_Lexer *lexer, t_main *db)
{
	char	current_char;
	char	*value;

	skip_whitespace(lexer, &value);
	if (lexer->input[lexer->pos] == '\0')
		return (create_token(EOF_TOKEN, NULL, db));
	current_char = lexer->input[lexer->pos];
	if (current_char == '\'' || current_char == '"')
		value = read_quoted_string(lexer, current_char, db);
	if (current_char == '\'' || current_char == '"')
		return (create_token(STRING, value, db));
	if (i_s_v_c(current_char))
	{
		value = read_id(lexer, db);
		if (value && value[0] == '$' && !fev(db->env_tab, value)
			&& value[1] != '\0' && value[1] != '?')
			return (create_token(IDENTIFIER, NULL, db));
		if (lexer->is_cmd == 1)
		{
			lexer->is_cmd = 0;
			return (create_token(IDENTIFIER, value, db));
		}
		return (create_token(ARGUMENT, value, db));
	}
	return (try_last_token(lexer, current_char, value, db));
}
