/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:21:35 by mgigot            #+#    #+#             */
/*   Updated: 2024/03/05 18:12:08 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	is_valid_arg(t_Token *token_arr)
{
	if (token_arr[0].type == PIPE || token_arr[0].type == EOF_TOKEN)
		return (1);
	return (0);
}

int	parser(t_main *t)
{
	t_cmd		*node;
	t_parser	parser_tools;

	if (t->token_arr[t->i]->type == PIPE)
		return (parser_double_token_error(t, t->token_arr[t->i]));
	while (t->token_arr[t->i]->type != EOF_TOKEN)
	{
		if (t->token_arr[t->i]->type == PIPE)
			t->i++;
		if (handle_pipe_errors(t, t->token_arr[t->i], t->i))
			return (1);
		parser_tools = init_parser_tools(t->token_arr + t->i, t);
		node = initialize_cmd(&parser_tools);
		if (!node)
			parser_error(1, t);
		if (parser_tools.tools->redir_error == 1)
			return (1);
		if (!t->cmds_list)
			t->cmds_list = node;
		else
			ft_simple_cmdsadd_back(&t->cmds_list, node);
		while (is_valid_arg(t->token_arr[t->i]) == 0)
			t->i++;
	}
	return (0);
}

int	ft_arraysize(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[i] != NULL)
		i++;
	return (i);
}

void	count_pipes(t_Token **lexer_list, t_main *t)
{
	int	i;

	i = 0;
	t->cmds_list = NULL;
	while (lexer_list[i]->type != EOF_TOKEN)
	{
		if (lexer_list[i]->type == PIPE)
			t->pipes++;
		i++;
	}
	return ;
}

t_cmd	*initialize_cmd(t_parser *ptls)
{
	char	**s;
	int		i;
	int		j;
	int		arg_size;
	t_Token	**tmp;

	i = -1;
	j = -1;
	rm_redirections(ptls, ptls->lexer_list);
	arg_size = count_args(ptls->lexer_list);
	s = ft_calloc(arg_size + 1, sizeof(char *));
	if (!s)
		parser_error(1, ptls->tools);
	tmp = ptls->lexer_list;
	while (arg_size > 0)
	{
		if (tmp[++i]->value == NULL || tmp[i]->type == DONE)
			i++;
		if (tmp[i]->value)
		{
			s[++j] = ft_strdup(tmp[i]->value);
			arg_size--;
		}
	}
	return (ft_simple_cmdsnew(s, ptls->num_redirections, ptls->redirections));
}
