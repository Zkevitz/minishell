/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:54 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 18:45:05 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	find_closing_quote(t_Lexer *lexer, char quote_type)
{
	while (lexer->input[lexer->pos] != '\0' && 
		lexer->input[lexer->pos] != quote_type)
		lexer->pos++;
	return (lexer->pos);
}

int	find_index_quotes(const char *input)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\0' && input[i + 1] != ' ')
		{
			while (input[i] != '\0' && input[i] != ' ')
				i++;
			index = i;
		}
		if (input[i] == '\0')
			break ;
		i++;
	}
	return (index);
}

void	expand_for_quotes(char **input, char **env, t_main *db)
{
	while (is_dollar(*input) != -1)
	{
		if ((*input)[first(*input)] == '?')
			*input = replace_string(*input, ft_strdup("$?"), 
					ft_itoa(g_g.l_e_c), db);
		else
			expend(&(*input), env, db);
	}
}

char	*read_quoted_string(t_Lexer *lexer, char quote_type, t_main *db)
{
	int		start_pos;
	int		closing_quote_pos;
	int		quoted_string_length;
	char	*quoted_string;

	start_pos = lexer->pos + 1;
	lexer->pos++;
	while (lexer->input[lexer->pos] != '\0' && 
		lexer->input[lexer->pos] != quote_type)
		lexer->pos++;
	closing_quote_pos = lexer->pos;
	lexer->pos++;
	quoted_string_length = closing_quote_pos - start_pos;
	quoted_string = malloc(quoted_string_length + 1);
	if (!quoted_string)
		exit_free(db, 1);
	ft_strncpy(quoted_string, lexer->input + start_pos, quoted_string_length);
	quoted_string[quoted_string_length] = '\0';
	if (is_dollar(quoted_string) == -1 || quote_type == '\'')
		return (quoted_string);
	expand_for_quotes(&quoted_string, db->env_tab, db);
	return (quoted_string);
}
