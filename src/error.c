/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:07:05 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 18:52:42 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", 2);
	if (c)
	{
		ft_putchar_fd('`', 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("\': ", 2);
	}
	ft_putendl_fd("not a valid identifier", 2);
	return (2);
}

void	parser_error(int error, t_main *tools)
{
	exit_free(tools, error);
}

int	ft_error(int error, t_main *tools)
{
	(void)tools;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	return (1);
}

int	parser_double_token_error(t_main *tools, t_Token *token)
{
	(void)tools;
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token->value[0] == '>' && token->value[1] == '\0')
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token->value[0] == '>' && token->value[1] == '>')
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token->value[0] == '<' && token->value[1] == '\0')
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token->value[0] == '<' && token->value[1] == '<')
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token->type == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	path_not_found(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (127);
}
