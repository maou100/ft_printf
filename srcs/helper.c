/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:17:05 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 12:25:15 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	ft_pf_putstr(char *str)
{
	int		i;
	char	zero;

	zero = '\0';
	i = -1;
	while (str[++i])
	{
		if (str[i] == 1)
		{
			if (g_c_bool)
				write(1, &zero, 1);
			else
				write(1, &str[i], 1);
		}
		else
			write(1, &str[i], 1);
	}
}

int		get_base(char c)
{
	if (c == 'o' || c == 'O')
		return (8);
	if (c == 'u' || c == 'U')
		return (10);
	if (c == 'x' || c == 'X' || c == 'p')
		return (16);
	return (0);
}

void	ft_init_params(t_params *par)
{
	par->hash = 0;
	par->zero = 0;
	par->min = 0;
	par->plus = 0;
	par->space = 0;
	par->width = -1;
	par->prec = -1;
	par->modif = 0;
	par->type = 0;
}
