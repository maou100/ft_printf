/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:53:09 by feedme            #+#    #+#             */
/*   Updated: 2018/09/13 14:08:48 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define ISFLAG(x) (x == '#' || x == '0' || x == '-' || x == '+' || x == ' ')
# define ISMODIF(x) (x == 'h' || x == 'l' || x == 'j' || x == 'z')
# define IS_ANYFLAG(x) (ISFLAG(x) || ISMODIF(x) || ISDIGIT(x) || x == '.')
# define IS_TYPE1(x) (x == 's' || x == 'S' || x == 'p' || x == 'd')
# define IS_TYPE2(x) (x == 'D' || x == 'i' || x == 'o' || x == 'O' || x == 'u')
# define IS_TYPE3(x) (x == 'U' || x == 'x' || x == 'X' || x == 'c' || x == 'C')
# define IS_TYPE(x) (x == '%' || IS_TYPE1(x) || IS_TYPE2(x) || IS_TYPE3(x))

typedef struct	s_params
{
	char		hash;
	char		zero;
	char		min;
	char		plus;
	char		space;
	int			width;
	int			prec;
	char		modif;
	char		type;
}				t_params;

typedef char*	(*t_fcts)(va_list ap, t_params par);

//typedef struct	s_functions
//{
//	char		type;
//	char		*fct(va_list ap);
//}				t_fcts;

int				g_c_bool;

char			*ft_imaxtoa(intmax_t nb);
char			*shift_right(char *str, int dist);
void			ft_pf_putstr(char *str);
char			*apply_hash(char *str, t_params par, int og_len, int prec_len);
int				ft_printf(const char *format, ...);
char			*uitoa_base(uintmax_t nb, int base, t_params par);
void			ft_get_params(const char *s, int *i, t_params *par);
void			ft_init_params(t_params *par);
char			*get_nbrs(va_list ap, t_params par);
char			*get_char(va_list ap, t_params par);
char			*get_perc(va_list ap, t_params par);
char			*get_str(va_list ap, t_params par);
char			*ft_perc(char *str, int *i, const char *s, va_list ap);
void			ft_get_params(const char *s, int *i, t_params *par);
void			ft_init_params(t_params *par);
int				get_base(char c);

#endif
