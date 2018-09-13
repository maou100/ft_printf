/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:50:42 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 12:44:42 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char	*ft_no_perc(char *str, int *i, const char *s)
{
	char	*tmp;
	char	*tmp2;
	int		i0;

	i0 = *i;
	while (s[*i] && s[*i] != '%')
		(*i)++;
	IF_NULL_X((tmp = ft_strsub(s, i0, (*i - i0))), -1)
	IF_NULL_X((tmp2 = ft_strjoin(str, tmp)), -1)
	free(str);
	free(tmp);
	return (tmp2);
}

int		ft_do_something(const char *s, va_list ap)
{
	int			len;
	char		*str;
	int			i;

	len = 0;
	i = 0;
	IF_NULL_R((str = ft_strnew(0)), -1)
	while (s[i])
	{
		if (s[i] != '%')
		{
			IF_NULL_R((str = ft_no_perc(str, &i, s)), -1)
		}
		else
		{
			IF_NULL_R((str = ft_perc(str, &i, s, ap)), -1)
		}
	}
	ft_pf_putstr(str);
	len = ft_strlen(str);
	free(str);
	return (len);
}

int		ft_printf(const char *format, ...)
{
	int			ret;
	va_list		ap;

	g_c_bool = 0;
	IF_NULL_R(format, -1)
	IF_NULL_R(*format, 0)
	va_start(ap, format);
	ret = ft_do_something(format, ap);
	va_end(ap);
	return (ret);
}
