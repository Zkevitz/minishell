/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:45 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 16:59:50 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*start;

	start = dest;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (n)
	{
		*dest = *src;
		++dest;
		++src;
		if (*(src - 1) == '\0')
			break ;
		--n;
	}
	while (n)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	return (start);
}
