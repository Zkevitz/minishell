/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:07:12 by rheck             #+#    #+#             */
/*   Updated: 2024/03/06 11:26:06 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	init_shell(char **env, t_main *data_base)
{
	char	*str;

	data_base->env_tab = ft_arraydup(env);
	data_base->env_path = fev(data_base->env_tab, "PATH");
	str = getenv("PWD");
	data_base->pwd = ft_strdup(str);
	str = getenv("OLWPWD");
	data_base->old_pwd = ft_strdup(str);
	free(str);
	data_base->i = 0;
	data_base->fork_index = 0;
	data_base->redirection = 0;
	data_base->redir_i = 0;
	data_base->redir_error = 0;
	data_base->export_error = 0;
	data_base->heredoc = 0;
	data_base->pipes = 0;
	data_base->sh_lvl = get_sh_lvl(getenv("SHLVL"));
	data_base->sh_lvl += 1;
	data_base->cmds_list = NULL;
	data_base->token_arr = NULL;
	data_base->pid = NULL;
	sh_lvl_up(data_base);
	init_signal();
	return (0);
}

int	get_sh_lvl(char *str)
{
	int	result;

	result = ft_atoi(str + equal_sign(str));
	return (result);
}
