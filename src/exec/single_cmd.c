/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:39:42 by mgigot            #+#    #+#             */
/*   Updated: 2024/03/05 18:45:05 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

void	ft_simple_cmdsclear(t_cmd **lst)
{
	t_cmd			*tmp;
	t_redir			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->red;
		ft_redirclear(&redirections_tmp);
		if ((*lst)->cmd_args)
			free_arr((*lst)->cmd_args);
		if ((*lst)->file_name)
			free((*lst)->file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_redirclear(t_redir **lst)
{
	t_redir	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->redir_name)
			free((*lst)->redir_name);
		if ((*lst)->redir_nam2)
			free((*lst)->redir_nam2);
		if ((*lst)->redirect)
			free((*lst)->redirect);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	single_cmd(t_cmd *cmd, t_main *tools)
{
	int	pid;
	int	status;

	if (!cmd)
		return ;
	cmd->builtin = look_for_builtin(cmd->cmd_name);
	if (cmd->builtin == my_cd || cmd->builtin == my_exit
		|| cmd->builtin == my_export || cmd->builtin == my_unset)
	{
		g_g.l_e_c = cmd->builtin(tools, cmd);
		return ;
	}
	if (send_heredoc(tools, cmd))
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		handle_cmd(cmd, tools);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_g.l_e_c = WEXITSTATUS(status);
}

int	check_fd_heredoc(t_main *tools, int end[2], t_cmd *cmd)
{
	int	fd_in;

	if (tools->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!str1 || !str2)
		return (1);
	if (n == 0)
		return (0);
	while (str1[i] != '\0' && str2[i] != '\0' && n - 1 > 0)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
		n--;
	}
	return (str1[i] - str2[i]);
}
