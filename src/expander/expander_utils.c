/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:58:44 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 12:59:26 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	find_var_end(char *arg, int start)
{
	int	i;

	i = start + 1;
	if (arg[i] == '?' || arg[i] == '$')
		i++;
	else
	{
		while (is_valid_var_char(arg[i]))
			i++;
	}
	return (i);
}

char	*start_of_env(char *arg)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (arg[i] != '$')
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ptr[j] = arg[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*extract_var_name(char *arg, int start, int end)
{
	char	*ptr;
	int		k;
	int		j;

	ptr = malloc((end - start) * sizeof(char));
	if (!ptr)
		return (NULL);
	k = 0;
	j = start + 1;
	while (j < end)
	{
		ptr[k] = arg[j];
		k++;
		j++;
	}
	ptr[k] = '\0';
	return (ptr);
}
