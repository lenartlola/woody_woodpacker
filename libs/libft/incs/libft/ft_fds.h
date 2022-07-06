/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:41:06 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/07 16:19:53 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDS_H
# define FT_FDS_H

// GET_NEXT_LINE
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_SIZE
#  define FD_SIZE 1
# endif

char	*get_next_line(int fd);

int 	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif
