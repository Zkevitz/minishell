/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:46 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 18:24:26 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

void	exit_free(t_main *db, int err)
{
	ft_error(err, db);
	free_all(db);
	exit(EXIT_FAILURE);
}

char	*find_env(char **envp, char *to_find)
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
		return (*envp + ft_strlen(to_find) + 1);
}

char	**ft_arraydup(char **tab)
{
	char	**new_array;
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	new_array = ft_calloc(sizeof(char *), i + 1);
	if (!new_array)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		new_array[i] = ft_strdup(tab[i]);
		if (new_array[i] == NULL)
		{
			free_arr(new_array);
			return (NULL);
		}
		i++;
	}
	return (new_array);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
	split_arr = NULL;
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s1)
		free(s1);
	s1 = NULL;
	return (result);
}
