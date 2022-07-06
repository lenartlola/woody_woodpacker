/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:48:56 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/07 16:28:14 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_fds.h"
# include "ft_chars.h"
# include "ft_strs.h"
# include "ft_nbrs.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define SPEC "cspdiuxX%"

typedef struct s_otions
{
	int		negative;
	int		zero;
	int		width;
	int		precision;
	char	spec;
	int		nbr_base;
	int		sign;
}	t_options;

int		ft_printf(int fd, const char *format, ...);
int		parse_format(va_list ap, char *format, int fd);
void	check_flags(va_list ap, char *format, t_options *option, int i);
void	width_precision(va_list ap, char *format, t_options *option, int i);
int		ft_print(va_list ap, t_options *option, int fd);
int	    ft_print_c(int c, t_options *option, int fd);
int		put_width_c(int width, int len, int zero, int fd);
int		ft_print_str(char *str, t_options *option, int fd);
int		put_width_str(char **buffer, t_options *option);
char	*parse_buffer(char *str, int end, int len);
int		ft_print_nbr(unsigned long long nbr, t_options *option, int fd);
int		ft_put_precision(unsigned long long nbr,
			t_options *option, char **buffer);
int		ft_put_minus(t_options *option, char **buffer);
int		ft_put_minus1(int buffer_len, t_options *option, char **buffer);
int		ft_ptr_prefix(char **buffer);
int		ft_nbrlen(unsigned long long nbr, t_options *option);
void	init(t_options *option);
char	*ft_baseset(char spec);

#endif
