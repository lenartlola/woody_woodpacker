/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:35:45 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/07 11:25:44 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_printf.h>

// Print a character
int	ft_print_c(int c, t_options *option, int fd)
{
	int	ret;

	ret = 0;
	if (option->spec == '%' && option->negative == 1)
		option->zero = 0;
	if (option->negative == 1)
		ret += ft_putchar_fd(c, fd);
	ret += put_width_c(option->width, 1, option->zero, fd);
	if (option->negative == 0)
		ret += ft_putchar_fd(c, fd);
	return (ret);
}

int	put_width_c(int width, int len, int zero, int fd)
{
	int	ret;

	ret = 0;
	while (len < width)
	{
		if (zero == 1)
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		len++;
		ret++;
	}
	return (ret);
}
