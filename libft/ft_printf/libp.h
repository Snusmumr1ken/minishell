/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyvchyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:57:24 by anyvchyk          #+#    #+#             */
/*   Updated: 2019/01/15 16:57:26 by anyvchyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBP_H
# define LIBP_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <inttypes.h>
# include <locale.h>

typedef enum	e_len
{
	none,
	hh,
	h,
	ll,
	j,
	l,
	L,
	z
}				t_len;

typedef struct	s_format
{
	char		type;
	int			sign_plus;
	int			sign_minus;
	int			sign_null;
	int			sign_hash;
	int			sign_space;
	int			width;
	int			precision;
	t_len		len;
}				t_format;

typedef struct	s_unicode
{
	char		byte[4];
}				t_unicode;

int				is_type(char c);
void			print_format(t_format format);
int				what_to_manage(t_format fmt, va_list *ap);
int				manage_char(t_format fmt, va_list *ap);
int				manage_string(t_format fmt, va_list *ap);
int				manage_pointer(t_format fmt, va_list *ap);
int				manage_decimal(t_format fmt, va_list *ap);
int				manage_unsigned(t_format fmt, va_list *ap);
int				manage_octal(t_format fmt, va_list *ap);
int				manage_binary(t_format fmt, va_list *ap);
int				manage_hex(t_format fmt, va_list *ap);
int				manage_percent(t_format fmt);
int				manage_float(t_format fmt, va_list *ap);
int				set_format(const char *format, int i,
								t_format *fmt, va_list *ap);
int				ft_printf(const char *format, ...);
int				ft_putchar(unsigned n);
int				ft_putstr(char *str);
int				ft_strlen(const char *str);
int				ft_atoi(const char *str);
char			*ft_itoa_base_signed(long long value, int base);
char			*ft_itoa_base_unsigned(unsigned long long value,
												int base);
char			*ftoa(long double number, int precision);
void			check_and_set_len(const char *str,
		int *i, t_format *fmt);

#endif
