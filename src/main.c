/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:39 by rheck             #+#    #+#             */
/*   Updated: 2024/03/06 11:25:49 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

void	my_header(void)
{
	printf("___  ___      _____ _          _ _ \n");
	printf("|  \\/  |     /  ___| |        | | |\n");
	printf("| .  . |_   _\\ `--.| |__   ___| | |\n");
	printf("| |\\/| | | | |`--. \\ '_ \\ / _ \\ | |\n");
	printf("| |  | | |_| /\\__/ / | | |  __/ | |\n");
	printf("\\_|  |_/\\__, \\____/|_| |_|\\___|_|_|\n");
	printf("         __/ |                     \n");
	printf("        |___/                      \n");
}

int	count_token(t_Lexer *lexer, char *prompt, t_main *db)
{
	int		result;
	t_Token	*token_count;

	init_lexer(lexer, prompt);
	token_count = get_next_token(lexer, db);
	result = 0;
	(void)prompt;
	while (token_count->type != EOF_TOKEN)
	{
		free(token_count->value);
		free(token_count);
		token_count = get_next_token(lexer, db);
		result++;
	}
	free(token_count);
	token_count = NULL;
	return (result);
}

int	reset_data_base(t_main *data_base)
{
	data_base->i = 0;
	data_base->fork_index = 0;
	data_base->redirection = 0;
	data_base->heredoc = 0;
	data_base->pipes = 0;
	data_base->export_error = 0;
	data_base->redir_error = 0;
	data_base->token_arr = NULL;
	data_base->pid = NULL;
	g_g.in_cmd = 0;
	g_g.in_heredoc = 0;
	g_g.stop_heredoc = 0;
	return (0);
}

int	free_all(t_main *data_base)
{
	int	i;

	i = 0;
	while (data_base->token_arr && data_base->token_arr[i]
		&& data_base->token_arr[i]->type != EOF_TOKEN)
	{
		if (data_base->token_arr[i]->value)
			free(data_base->token_arr[i]->value);
		if (data_base->token_arr[i])
			free(data_base->token_arr[i]);
		i++;
	}
	if (data_base->pid)
		free(data_base->pid);
	if (data_base->token_arr && data_base->token_arr[i])
		free(data_base->token_arr[i]);
	if (data_base->token_arr)
		free(data_base->token_arr);
	ft_simple_cmdsclear(&data_base->cmds_list);
	if (data_base->my_prompt_line)
		free(data_base->my_prompt_line);
	data_base->my_prompt_line = NULL;
	reset_data_base(data_base);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_main	db;

	init_shell(env, &db);
	while (1)
	{
		db.my_prompt_line = readline("\033[1;32mMy prompt \033[0m");
		if (db.my_prompt_line == NULL)
			return (0);
		if (!check_propmt(db.my_prompt_line, argc, argv))
			ft_error(2, &db);
		else if (db.my_prompt_line && db.my_prompt_line[0] != '\0')
		{
			process(&db);
			expand_var(&db);
			count_pipes(db.token_arr, &db);
			if (!parser(&db))
				prepare_execute(&db);
			super_history(db.my_prompt_line);
			free_all(&db);
		}
		free (db.my_prompt_line);
		db.my_prompt_line = NULL;
		reset_data_base(&db);
	}
	return (0);
}
