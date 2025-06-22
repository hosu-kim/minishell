/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:59:53 by jaandras          #+#    #+#             */
/*   Updated: 2025/06/22 22:00:23 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*str_cpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	get_num_len(int n)
{
	int	num_len;

	num_len = 0;
	if (n <= 0)
		num_len++;
	while (n)
	{
		n /= 10;
		num_len++;
	}
	return (num_len);
}

static char	*convert_number(int n, int num_len)
{
	char	*ptr;
	int		i;

	i = num_len - 1;
	ptr = (char *)malloc((num_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[num_len] = '\0';
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
	{
		ptr[0] = '-';
		n = -n;
	}
	while (n)
	{
		ptr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		num_len;
	char	*result;

	if (n == -2147483648)
	{
		result = malloc(12 * sizeof(char));
		if (!result)
			return (NULL);
		return (str_cpy(result, "-2147483648"));
	}
	num_len = get_num_len(n);
	result = convert_number(n, num_len);
	return (result);
}
