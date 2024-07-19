/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:00:35 by rheck             #+#    #+#             */
/*   Updated: 2024/03/05 18:18:20 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_propmt(char *prompt, int argc, char **argv)
{
	int	single;
	int	doble;
	int	i;

	(void)argc;
	(void)argv;
	single = 0;
	doble = 0;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' && !doble)
			single = !single;
		else if (prompt[i] == '\"' && !single)
			doble = !doble;
		i++;
	}
	return (single % 2 == 0 && doble % 2 == 0);
}
