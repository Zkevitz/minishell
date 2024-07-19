/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:04:07 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 11:33:01 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	count_args(t_Token **lexer_list)
{
	t_Token	**tmp;
	int		i;
	int		count;

	i = 0;
	count = 0;
	tmp = lexer_list;
	while (tmp[i]->type != EOF_TOKEN && tmp[i]->type != PIPE)
	{
		if (tmp[i]->type != DONE && tmp[i]->value != NULL)
			count++;
		i++;
	}
	return (count);
}

int	count_redirect(t_Token *lexer_list)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (lexer_list[i].type != PIPE && lexer_list[i].type != EOF_TOKEN)
	{
		if (lexer_list[i].type == OPERATOR)
			count++;
		i++;
	}
	return (count);
}

void	ft_lexeradd_back(t_redir **lst, t_redir *new)
{
	t_redir	*p;

	p = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (p->next != NULL)
		p = p->next;
	p->next = new;
	new->prev = p;
}

int	handle_pipe_errors(t_main *tools, t_Token *token, int i)
{
	if (token->type == PIPE)
	{
		parser_double_token_error(tools, token);
		return (1);
	}
	if (tools->token_arr[i]->type == EOF_TOKEN)
	{
		parser_error(0, tools);
		return (1);
	}
	return (0);
}

void	ft_simple_cmdsadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
