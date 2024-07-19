/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:36:42 by mgigot            #+#    #+#             */
/*   Updated: 2024/03/05 17:54:16 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	check_append_outfile(t_redir *redirections)
{
	int	fd;

	if (redirections->redirect[0] == '>' && redirections->redirect[1] == '>')
		fd = open(redirections->redir_name,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirections->redir_name,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	handle_outfile(t_redir *redirection)
{
	int	fd;

	fd = check_append_outfile(redirection);
	if (fd < 0)
	{
		if (!access(redirection->redir_name, W_OK))
			ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		else
			permission_error(redirection->redir_name);
		return (1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	check_redirections(t_cmd *c)
{
	t_redir	*start;

	start = c->red;
	while (c->red)
	{
		if (c->red->redirect[0] == '<' && c->red->redirect[1] == '\0')
		{
			if (handle_infile(c->red->redir_name))
				return (1);
		}
		else if ((c->red->redirect[0] == '>' && c->red->redirect[1] == '\0')
			|| (c->red->redirect[0] == '>' && c->red->redirect[1] == '>'))
		{
			if (handle_outfile(c->red))
				return (1);
		}
		else if (c->red->redirect[0] == '<' && c->red->redirect[1] == '<')
		{
			if (handle_infile(c->file_name))
				return (1);
		}
		c->red = c->red->next;
	}
	c->red = start;
	return (0);
}
