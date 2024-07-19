/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:34:12 by mgigot            #+#    #+#             */
/*   Updated: 2024/03/05 18:45:05 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	ft_fork(t_main *data_base, int end[2], int fd_in, t_cmd *cmd)
{
	data_base->pid[data_base->fork_index] = fork();
	if (data_base->pid[data_base->fork_index] < 0)
		ft_error(5, data_base);
	if (data_base->pid[data_base->fork_index] == 0)
		dup_cmd(cmd, data_base, end, fd_in);
	data_base->fork_index++;
	return (0);
}

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_g.l_e_c = WEXITSTATUS(status);
	return (0);
}

void	dup_cmd(t_cmd *cmd, t_main *tools, int end[2], int fd_in)
{
	if (cmd->prev && (dup2(fd_in, 0) < 0))
	{
		ft_error(4, tools);
	}
	close(end[0]);
	if (cmd->next && dup2(end[1], 1) < 0)
	{
		ft_error(4, tools);
	}
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, tools);
}

void	handle_cmd(t_cmd *cmd, t_main *tools)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd_name == NULL)
		return ;
	if (cmd->red != NULL)
	{
		if (check_redirections(cmd))
			exit(1);
	}
	if ((look_for_builtin(cmd->cmd_name)))
	{
		cmd->builtin = look_for_builtin(tools->cmds_list->cmd_name);
		exit_code = cmd->builtin(tools, cmd);
		exit(exit_code);
	}
	else if (cmd->cmd_args[0][0] != '\0')
		exit_code = find_cmd(cmd, tools);
	exit(exit_code);
}

int	find_cmd(t_cmd *cmd, t_main *tools)
{
	int		i;
	char	**path_exec;
	char	*tmp;
	char	*mycmd;

	i = -1;
	if (tools->env_path == NULL)
		return (path_not_found(cmd->cmd_name));
	if (!access(cmd[0].cmd_name, X_OK))
		execve(cmd[0].cmd_name, cmd[0].cmd_args, tools->env_tab);
	path_exec = ft_split(tools->env_path, ':');
	while (path_exec[++i])
	{
		tmp = ft_strjoin(path_exec[i], "/");
		mycmd = ft_strjoin(tmp, cmd[0].cmd_name);
		free(tmp);
		if (!access(mycmd, F_OK))
		{
			free_arr(path_exec);
			execve(mycmd, cmd->cmd_args, tools->env_tab);
		}
		free(mycmd);
	}
	free_arr(path_exec);
	return (cmd_not_found(cmd->cmd_name));
}
