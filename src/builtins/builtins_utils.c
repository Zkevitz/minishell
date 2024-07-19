/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:53:53 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 16:27:17 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

size_t	equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

// char	**ft_join_arg(t_cmd *simple_cmd)
// {
// 	char	**new_tab;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	new_tab = malloc(sizeof(char *) * 3);
// 	if (!new_tab)
// 		return (NULL);
// 	tmp = ft_strjoin(simple_cmd->cmd_args[1], simple_cmd->cmd_args[2]);
// 	if (!tmp)
// 		return (NULL);
// 	new_tab[0] = ft_strdup(simple_cmd->cmd_args[0]);
// 	new_tab[1] = ft_strdup(tmp);
// 	free(tmp);
// 	tmp = NULL;
// 	new_tab[2] = NULL;
// 	free_arr(simple_cmd->cmd_args);
// 	simple_cmd->cmd_args = NULL;
// 	return (new_tab);
// }

char	*delete_quotes_value(char *str)
{
	char	**split_quotes;

	split_quotes = ft_split(str, '"');
	if (!split_quotes[1])
	{
		free_arr(split_quotes);
		split_quotes = ft_split(str, '\'');
	}
	free(str);
	str = ft_strjoin(split_quotes[0], split_quotes[1]);
	free_arr(split_quotes);
	return (str);
}

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}
