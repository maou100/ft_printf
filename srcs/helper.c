/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:17:05 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 19:43:38 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char		*ft_str_left_ext(char *str, int extension)
{
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(str) + extension;
	i = 0;
	IF_NULL_R((tmp = ft_strnew(len)), NULL);
	ft_bzero(tmp, len);
	while ((extension + i) < len)
	{
		tmp[extension + i] = str[i];
		i++;
	}
	return (tmp);
}

char		*enuf_space(char *str, t_params par)
{
	int		i;

	i = 0;
	if (par.min)
	{
		str = shift_right(str, 2);
		str[0] = '0';
		str[1] = par.type == 'X' ? 'X' : 'x';
		return (str);
	}
	else
	{
		if (par.zero)
		{
			str[1] = par.type == 'X' ? 'X' : 'x';
			return (str);
		}
		while (str[i] == ' ')
			i++;
		str[i - 2] = '0';
		str[i - 1] = par.type == 'X' ? 'X' : 'x';
		return (str);
	}
}

void		ft_pf_putstr(char *str)
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

int			get_base(char c)
{
	if (c == 'o' || c == 'O')
		return (8);
	if (c == 'u' || c == 'U')
		return (10);
	if (c == 'x' || c == 'X' || c == 'p')
		return (16);
	return (0);
}

void		ft_init_params(t_params *par)
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
