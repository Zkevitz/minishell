/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:37:11 by rheck             #+#    #+#             */
/*   Updated: 2024/03/06 11:55:52 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	*ft_strcpy(char *dest, char *src)
{
	char	*start;
	char	*temp;

	start = dest;
	temp = src;
	if (!dest || !src)
		return (NULL);
	while (*temp != '\0')
		++temp;
	while (*src != '\0')
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	return (start);
}

char	*my_strstr(char *haystack, char *needle)
{
	const char	*h;
	const char	*n;

	if (!haystack)
		return (NULL);
	if (!needle)
		return (NULL);
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

char	*replace_string(char *input, char *old, char *new, t_main *db)
{
	char	*found;
	int		result_len;
	char	*result;

	if (old[0] == '$' && old[1] == '\0')
		return (replace_pid(input, old, new, db));
	found = my_strstr(input, old);
	if (!found)
		exit_free(db, 1);
	result_len = (found - input) + ft_strlen(new) 
		+ (ft_strlen(input) - ft_strlen(old));
	result = (char *)malloc((result_len + 1) * sizeof(char));
	if (!result)
		exit_free(db, 1);
	ft_strncpy(result, input, (found - input));
	ft_strcpy(result + (found - input), new);
	ft_strcpy(result + (found - input) 
		+ ft_strlen(new), found + ft_strlen(old));
	result[result_len] = '\0';
	if (old)
		free(old);
	free(new);
	free(input);
	return (result);
}

int	is_dollar(char *input)
{
	int	i;

	if (!input)
		return (-1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\0' && input[i + 1] != ' ')
			return (i);
		i++;
	}
	return (-1);
}

int	first(char *input)
{
	return (is_dollar(input) + 1);
}
