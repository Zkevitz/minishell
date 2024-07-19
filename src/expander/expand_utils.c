/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:58:22 by rheck             #+#    #+#             */
/*   Updated: 2024/03/06 11:33:44 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h" // anciennement fichier expender 2

int	get_var_end(char *input)
{
	int	i;

	if (!input)
		return (-1);
	i = is_dollar(input) + 1;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '$'
			|| input[i] == '\'' || input[i] == '\"')
			return (i);
		i++;
		if (!input[i])
			return (i);
	}
	return (-1);
}

char	*remove_string(char *input, char *string_to_remove, t_main *db)
{
	char	*found;
	int		result_len;
	char	*result;

	found = my_strstr(input, string_to_remove);
	if (!found)
		return (input);
	result_len = ft_strlen(input) - ft_strlen(string_to_remove);
	result = (char *)malloc((result_len + 1) * sizeof(char));
	if (!result)
		exit_free(db, 1);
	ft_strncpy(result, input, found - input);
	ft_strcpy(result + (found - input), found + ft_strlen(string_to_remove));
	result[result_len] = '\0';
	if (result[0] == '\0')
		return (NULL);
	free(string_to_remove);
	free(input);
	return (result);
}

char	*get_dollar_name(char *input, t_main *db)
{
	char	*var_name;

	var_name = malloc(sizeof(char) * 
			(get_var_end(input) - (is_dollar(input)) + 1));
	if (!var_name)
		exit_free(db, 1);
	strlcpy(var_name, &input[is_dollar(input)],
		get_var_end(input) - (is_dollar(input)) + 1);
	return (var_name);
}

char	*get_var_name(char *input, t_main *db)
{
	char	*var_name;

	var_name = malloc(sizeof(char) * 
			(get_var_end(input) - (first(input)) + 1));
	if (!var_name)
		exit_free(db, 1);
	ft_strlcpy(var_name, &input[first(input)],
		get_var_end(input) - (first(input)) + 1);
	return (var_name);
}

void	expend(char **input, char **env, t_main *db)
{
	char	*var_name;
	char	*dollar_name;
	char	*copy;

	copy = ft_strdup(*input);
	if (is_dollar(copy) == -1)
	{
		free(copy);
		return ;
	}
	free(*input);
	var_name = get_var_name(copy, db);
	if ((copy)[first(copy)] == '?')
		*input = replace_string(copy, ft_strdup("$?"), ft_itoa(g_g.l_e_c), db);
	else if (find_env(env, var_name))
		*input = replace_string(copy,
				ft_strjoin2(ft_strdup("$"), var_name), fev(env, var_name), db);
	else
	{
		dollar_name = get_dollar_name(copy, db);
		*input = remove_string(copy, dollar_name, db);
	}
	if (var_name)
		free(var_name);
}
