/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:37:14 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/28 23:12:17 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Counts the length of the provided string.
 */
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief Copies provided string to the duplicate and return it.
 */
char	*ft_strdup(const char *s)
{
	int		str_len;
	int		i;
	char	*dup;

	str_len = ft_strlen(s);
	dup = (char *)malloc((str_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
