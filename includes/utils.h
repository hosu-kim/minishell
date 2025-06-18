/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:38:18 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/17 21:39:13 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *str1, const char *str2);
void	ft_putendl_fd(char *s, int fd);

#endif
