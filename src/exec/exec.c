/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:17:41 by mgigot            #+#    #+#             */
/*   Updated: 2024/03/06 11:24:51 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	*fev(char **envp, char *to_find)
{
	int		cond;
	int		i;

	i = 0;
	cond = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], to_find, ft_strlen(to_find)) == 0)
			cond = 1;
		i++;
	}
	while (ft_strncmp(to_find, *envp, ft_strlen(to_find)) && *envp)
		envp++;
	if (cond == 0)
		return (NULL);
	else
		return (ft_strdup(*envp + ft_strlen(to_find) + 1));
}

int	prepare_execute(t_main *data_base)
{
	signal(SIGQUIT, sigquit_handler);
	g_g.in_cmd = 1;
	if (data_base->pipes == 0)
		single_cmd(data_base->cmds_list, data_base);
	else
	{
		data_base->pid = ft_calloc(sizeof(int), data_base->pipes + 2);
		if (!data_base->pid)
			return (ft_error(1, data_base));
		execute(data_base);
	}
	signal(SIGQUIT, SIG_IGN);
	g_g.in_cmd = 0;
	return (0);
}

int	sh_lvl_up(t_main *data_base)
{
	int		i;
	char	*tmp;
	char	*nb;

	i = 0;
	nb = ft_itoa(data_base->sh_lvl);
	if (!nb)
		return (1);
	while (data_base->env_tab[i])
	{
		if (ft_strncmp(data_base->env_tab[i], "SHLVL=", 6) == 0)
		{
			free(data_base->env_tab[i]);
			tmp = ft_strjoin("SHLVL=", nb);
			free(nb);
			data_base->env_tab[i] = ft_strdup(tmp);
			free(tmp);
			return (0);
		}
		i++;
	}
	return (1);
}

int	execute(t_main *tools)
{
	int		end[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (tools->cmds_list)
	{
		if (tools->cmds_list->next)
		{
			pipe(end);
		}
		send_heredoc(tools, tools->cmds_list);
		ft_fork(tools, end, fd_in, tools->cmds_list);
		close(end[1]);
		if (tools->cmds_list->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(tools, end, tools->cmds_list);
		if (tools->cmds_list->next)
			tools->cmds_list = tools->cmds_list->next;
		else
			break ;
	}
	pipe_wait(tools->pid, tools->pipes);
	tools->cmds_list = ft_simple_cmdsfirst(tools->cmds_list);
	return (0);
}

t_cmd	*ft_simple_cmdsfirst(t_cmd *map)
{
	if (!map)
		return (NULL);
	while (map->prev != NULL)
		map = map->prev;
	return (map);
}
