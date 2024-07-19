/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:36:21 by mgigot            #+#    #+#             */
/*   Updated: 2024/03/05 18:45:05 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	create_heredoc(t_redir *hrd, bool quotes,
	t_main *tools, char *file_name)
{
	int		fd;
	char	*l;

	(void)quotes;
	(void)tools;
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	l = readline("\033[1;36mminishell\033[34m$ \033[0m");
	while (l && ft_strncmp2(hrd->redir_nam2, l, ft_strlen(hrd->redir_nam2))
		&& !g_g.stop_heredoc)
	{
		expend(&l, tools->env_tab, tools);
		if (!ft_strncmp2(hrd->redir_nam2, l, ft_strlen(hrd->redir_nam2)))
			break ;
		write(fd, l, ft_strlen(l));
		write(fd, "\n", 1);
		free(l);
		l = readline("\033[1;36mminishell\033[34m$ \033[0m");
	}
	free(l);
	if (g_g.stop_heredoc || !l)
		return (1);
	close(fd);
	return (0);
}

int	ft_heredoc(t_main *tools, t_redir *hrd, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = 0;
	if ((hrd->redir_name[0] == '\"'
			&& hrd->redir_name[ft_strlen(hrd->redir_name) - 1] == '\"')
		|| (hrd->redir_name[0] == '\''
			&& hrd->redir_name[ft_strlen(hrd->redir_name) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delete_quotes(hrd->redir_name, '\"');
	delete_quotes(hrd->redir_name, '\'');
	g_g.stop_heredoc = 0;
	g_g.in_heredoc = 1;
	sl = create_heredoc(hrd, quotes, tools, file_name);
	g_g.in_heredoc = 0;
	tools->heredoc = 1;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(".tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_main *tools, t_cmd *cmd)
{
	t_redir	*start;

	start = cmd->red;
	while (cmd->red)
	{
		if (cmd->red->redirect 
			&& ft_strncmp(cmd->red->redirect, "<<", 2) == 0)
		{
			if (cmd->file_name)
				free(cmd->file_name);
			cmd->file_name = generate_heredoc_filename();
			if (ft_heredoc(tools, cmd->red, cmd->file_name))
			{
				if (cmd->red->redir_nam2 == NULL)
					g_g.l_e_c = 258;
				else
					g_g.l_e_c = 1;
				return (1); 
			}
		}
		cmd->red = cmd->red->next;
	}
	cmd->red = start;
	return (0);
}
