/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbrs_hlper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 19:55:13 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 20:06:08 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

intmax_t	modif_ints(va_list ap, t_params par)
{
	intmax_t	nb;

	if (par.modif == 'l')
		nb = va_arg(ap, long);
	else if (par.modif == 'L')
		nb = va_arg(ap, long long);
	else if (par.modif == 'j')
		nb = va_arg(ap, intmax_t);
	else if (par.modif == 'z')
		nb = va_arg(ap, ssize_t);
	else
		nb = va_arg(ap, int);
	if (par.modif == 'h')
		nb = (short)nb;
	else if (par.modif == 'H')
		nb = (char)nb;
	return (nb);
}

uintmax_t	modif_uints(va_list ap, t_params par)
{
	uintmax_t	nb;

	if (par.modif == 'l')
		nb = va_arg(ap, unsigned long);
	else if (par.modif == 'L' || par.type == 'O' || par.type == 'U')
		nb = va_arg(ap, unsigned long long);
	else if (par.modif == 'j')
		nb = va_arg(ap, uintmax_t);
	else if (par.modif == 'z')
		nb = va_arg(ap, size_t);
	else
		nb = va_arg(ap, unsigned long long);
	if (par.modif == 'h')
		nb = (unsigned short)nb;
	else if (par.modif == 'H')
		nb = (unsigned char)nb;
	if ((par.type == 'x' || par.type == 'X') && nb > 4294967295 && !par.modif)
		return (0);
	return (nb);
}

void		fix_pb_hlper(char *str, int i)
{
	if (str[0] == '+' && str[1] == ' ')
	{
		i++;
		while (str[i] == ' ')
			i++;
		str[i - 1] = '+';
		str[0] = ' ';
	}
}

char		*ft_fix_pbs(char *str, t_params par, int booly)
{
	int			i;
	int			j;

	j = 0;
	i = 0;
	if (booly && (par.zero || par.prec != -1))
	{
		while (str[i] != '-')
			i++;
		if (i != 0)
		{
			str[i] = '0';
			while (str[j] != '0')
				j++;
			str[j] = '-';
		}
	}
	else if (par.plus && !par.zero)
		fix_pb_hlper(str, i);
	return (str);
}

char		*get_ints(va_list ap, t_params par)
{
	intmax_t	nb;
	char		*str;
	int			len;
	int			booly;

	booly = 0;
	if ((nb = modif_ints(ap, par)) < 0)
		booly = 1;
	if (!nb && !par.prec)
		str = ft_strnew(0);
	else
		IF_NULL_X((str = ft_imaxtoa(nb)), -1);
	len = ft_strlen(str);
	if (par.prec > (booly ? len - 1 : len))
		str = int_prec(str, par, booly);
	if (par.width > ft_strlen(str))
		str = int_width(str, par);
	if ((par.space && nb > 0) || (par.plus && nb >= 0))
		str = int_add_sign(str, par);
	str = ft_fix_pbs(str, par, booly);
	return (str);
}
