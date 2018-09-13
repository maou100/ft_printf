/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 22:52:20 by feedme            #+#    #+#             */
/*   Updated: 2018/09/10 03:36:20 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int		ft_spacecount(intmax_t n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_imaxtoa(intmax_t nb)
{
	char	*str;
	int		i;

	i = ft_spacecount(nb) - 1;
	if (!(str = ft_strnew(ft_spacecount(nb))))
		return (NULL);
	if (nb <= 0)
	{
		if (nb == 0)
		{
			str[0] = '0';
			return (str);
		}
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (str);
}
