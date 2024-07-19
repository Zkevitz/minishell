/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:21:54 by mgigot            #+#    #+#             */
/*   Updated: 2024/03/05 18:12:20 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

t_parser	init_parser_tools(t_Token **lexer_list, t_main *tools)
{
	t_parser	parser_tools;

	parser_tools.lexer_list = lexer_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = tools;
	return (parser_tools);
}

void	rm_redirections(t_parser *parser_tools, t_Token **lexer_list)
{
	t_Token	**p;
	int		i;

	i = 0;
	p = lexer_list;
	while (p[i]->type != EOF_TOKEN && p[i]->type
		!= OPERATOR && p[i]->type != PIPE)
		i++;
	if (p[i]->type == EOF_TOKEN || p[i]->type == PIPE)
		return ;
	if (p[i + 1]->type == EOF_TOKEN)
	{
		parser_error(0, parser_tools->tools);
		parser_tools->tools->redir_error = 1;
		return ;
	}
	if (p[i + 1]->type == OPERATOR || p[i + 1]->type == PIPE)
	{
		parser_double_token_error(parser_tools->tools, p[i]);
		parser_tools->tools->redir_error = 1;
		return ;
	}
	if (p[i]->type == OPERATOR)
		add_new_redirection(p + i, parser_tools);
	rm_redirections(parser_tools, lexer_list + i + 2);
}

int	add_new_redirection(t_Token **p, t_parser *parser_tools)
{
	t_redir	*node;

	node = ft_lexernew(ft_strdup(p[0]->value), ft_strdup(p[1]->value));
	if (!node)
		parser_error(1, parser_tools->tools);
	ft_lexeradd_back(&parser_tools->redirections, node);
	p[0]->type = DONE;
	free(p[0]->value);
	p[0]->value = NULL;
	p[1]->type = DONE;
	free(p[1]->value);
	p[1]->value = NULL;
	parser_tools->num_redirections++;
	return (0);
}

t_redir	*ft_lexernew(char *str, char *str2)
{
	t_redir		*new_element;
	static int	i = 0;

	new_element = (t_redir *)malloc(sizeof(t_redir));
	if (!new_element)
		return (0);
	new_element->redirect = str;
	new_element->redir_name = str2;
	new_element->redir_nam2 = ft_strdup(str2);
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

t_cmd	*ft_simple_cmdsnew(char **str,
	int num_redir, t_redir *redirect)
{
	t_cmd	*new_element;

	new_element = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_element)
		return (0);
	new_element->cmd_name = str[0];
	new_element->cmd_args = str;
	new_element->builtin = NULL;
	new_element->file_name = NULL;
	new_element->num_redirections = num_redir;
	new_element->red = redirect;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}
