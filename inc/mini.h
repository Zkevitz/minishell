/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:34:20 by rheck             #+#    #+#             */
/*   Updated: 2024/03/06 11:55:26 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>
# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_global {
	int		l_e_c;
	int		in_cmd;
	int		in_heredoc;
	int		stop_heredoc;
}	t_global;

t_global	g_g;

typedef enum s_TokenType {
	IDENTIFIER,
	NUMBER,
	OPERATOR,
	KEYWORD,
	STRING,
	EOF_TOKEN,
	OPTION,
	VARIABLE,
	ERROR,
	ARGUMENT,
	PIPE,
	DONE
}	t_TokenType;

typedef struct s_lexer {
	const char	*input;
	size_t		pos;
	int			is_cmd;
	int			in_cmd;
}	t_Lexer;

typedef struct s_Token {
	t_TokenType	type;
	char		*value;
}	t_Token;

typedef struct s_main
{
	char			*my_prompt_line;
	char			*env_path;
	char			**env_tab;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
	int				i;
	int				fork_index;
	int				redir_i;
	int				redirection;
	int				sh_lvl;
	int				redir_error;
	int				export_error;
	int				*output;
	int				history_file;
	int				heredoc;
	t_Token			**token_arr;
	struct s_cmd	*cmds_list;
}	t_main;

typedef struct s_redir {
	char			*redir_name;
	char			*redir_nam2;
	char			*redirect;
	int				i;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd {
	char			*cmd_name;
	char			**cmd_args;
	int				(*builtin)(t_main *, struct s_cmd *);
	int				num_redirections;
	char			*file_name;
	struct s_redir	*red;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_parser
{
	struct s_Token	**lexer_list;
	t_redir			*redirections;
	int				num_redirections;
	struct s_main	*tools;
}	t_parser;

// utils
char		*fev(char **envp, char *to_find);
void		free_arr(char **split_arr);
char		**ft_arraydup(char **tab);
int			ft_strncmp2(const char *s1, const char *s2, size_t n);
char		*ft_strjoin2(char *s1, char *s2);
char		*find_env(char **envp, char *to_find);

// initialisation
void		my_header(void);
int			init_shell(char **env, t_main *data_base);
void		process(t_main *data_base);
int			print_history(void);
int			count_token(t_Lexer *lexer, char *prompt, t_main *db);

// builtins
int			my_exit(t_main *tools, t_cmd *simple_cmd);
int			my_history(t_main *data_base, t_cmd *simple_cmd);
int			my_cd(t_main *tools, t_cmd *simple_cmd);
int			my_env(t_main *data_base, t_cmd *simple_cmd);
int			my_echo(t_main *tools, t_cmd *simple_cmd);
int			my_pwd(t_main *tools, t_cmd *simple_cmd);
int			my_unset(t_main *tools, t_cmd *simple_cmd);
int			my_export(t_main *tools, t_cmd *simple_cmd);
int			(*look_for_builtin(char *name))(t_main *db, t_cmd *single_cmd);

// builtins utils
void		super_history(char *str);
size_t		equal_sign(char *str);
int			check_valid_identifier(char c);
char		*delete_quotes_value(char *str);
char		*delete_quotes(char *str, char c);
int			sh_lvl_up(t_main *data_base);
void		change_env_tab(char *new_pos, t_main *tools, const char *to_find);
int			get_sh_lvl(char *str);
int			check_arg(char **tab, t_main *data_base);
char		**ft_join_arg(t_cmd *simple_cmd);

//signal 
void		init_signal(void);
void		sigquit_handler(int sig);

//free
int			clear_cmd_list(t_main **cmd_list);
int			free_all(t_main *data_base);
void		ft_redirclear(t_redir **lst);
void		ft_simple_cmdsclear(t_cmd **lst);

//exec 
int			execute(t_main *data_base);
int			prepare_execute(t_main *data_base);
int			send_heredoc(t_main *tools, t_cmd *cmd);
void		single_cmd(t_cmd *cmd, t_main *tools);
void		dup_cmd(t_cmd *cmd, t_main *tools, int end[2], int fd_in);
void		handle_cmd(t_cmd *cmd, t_main *tools);
int			handle_infile(char *file);
int			handle_outfile(t_redir *redirect);
int			find_cmd(t_cmd *cmd, t_main *tools);
t_cmd		*ft_simple_cmdsfirst(t_cmd *map);

// exec utils 
int			ft_fork(t_main *data_base, int end[2], int fd_in, t_cmd *cmd);
int			check_fd_heredoc(t_main *tools, int end[2], t_cmd *cmd);
int			pipe_wait(int *pid, int amount);
int			check_redirections(t_cmd *cmd);

//error msg 
int			export_error(char *c);
int			ft_error(int error, t_main *tools);
int			cmd_not_found(char *str);
void		permission_error(char *str);
int			path_not_found(char *str);
int			parser_double_token_error(t_main *tools, t_Token *token);
int			handle_pipe_errors(t_main *tools, t_Token *token, int pos);

// parsing
t_cmd		*parse_cmd(t_main *data_base);
t_cmd		parse_next_cmd(t_main *data_base);
int			is_valid_arg(t_Token *token_arr);
int			place_redirection(t_cmd **new_dir, t_main *data_base, int pos);
void		count_pipes(t_Token **lexer_list, t_main *tools);
int			count_args(t_Token **lexer_list);
t_parser	init_parser_tools(t_Token **lexer_list, t_main *tools);
t_cmd		*initialize_cmd(t_parser *parser_tools);
void		ft_simple_cmdsadd_back(t_cmd **lst, t_cmd *new);
void		rm_redirections(t_parser *parser_tools, t_Token **lexer_list);
void		parser_error(int error, t_main *tools);
t_cmd		*ft_simple_cmdsnew(char **str, int num_redir, t_redir *redirect);
int			add_new_redirection(t_Token **tmp, t_parser *parser_tools);
t_redir		*ft_lexernew(char *str, char *str2);
void		ft_lexeradd_back(t_redir **lst, t_redir *new);
int			parser(t_main *tools);
int			ft_arraysize(t_cmd *cmd);
int			check_propmt(char *prompt, int argc, char **argv);
void		exit_free(t_main *db, int err);

// robin lexer 
char		*replace_string(char *input, char *old, char *new, t_main *db);
void		init_lexer(t_Lexer *lexer, const char *input);
char		*read_q_s(char *input, char *old, t_main *db);
int			is_operator_char(char c);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			ft_isdigit(int c);
int			is_space(char c);
int			ft_isalpha(int c);
int			first(char *input);
char		wq(char *input);
void		expend(char **input, char **env, t_main *db);
char		*ft_strcpy(char *dest, char *src);
char		*my_strstr(char *haystack, char *needle);
t_Token		*get_next_token(t_Lexer *lexer, t_main *db);
char		*read_operator(t_Lexer *lexer, t_main *db);
char		*create_operator_str(t_Lexer *lexer, int start_position);
void		expand_for_quotes(char **input, char **env, t_main *db);
char		*read_regular_operator(t_Lexer *lexer, int start_position); //?
char		*read_double_quote(t_Lexer *lexer, int start_position);
int			f_q(char *input, char quote_type, int index);
char		*read_single_quote(t_Lexer *lexer, int start_position);
char		*read_quoted_string(t_Lexer *lexer, char quote_type, t_main *db);
char		*read_option(t_Lexer *lexer, t_main *db);
int			find_closing_quote(t_Lexer *lexer, char quote_type);
char		*read_id(t_Lexer *lexer, t_main *db);
int			i_s_v_c(char c);
char		*read_number(t_Lexer *lexer, t_main *db);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*complete_line(int length_1, const char *input, char *var_name);
void		expand_var(t_main *data_base);
int			is_dollar(char *input);
char		*replace_env_variables(char *input);
//char		*ft_itoa(int n);
char		*replace_pid(char *input, char *old, char *new, t_main *db);
#endif