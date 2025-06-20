/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:21:03 by jakand            #+#    #+#             */
/*   Updated: 2025/06/20 19:25:24 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	update_token(char **arg, char *start, int j)
{
	int		i;
	int		l;
	char	*ptr;

	j++;
	while (((*arg)[j] >= '0' && (*arg)[j] <= '9')
		|| ((*arg)[j] >= 'a' && (*arg)[j] <= 'z')
		|| ((*arg)[j] >= 'A' && (*arg)[j] <= 'Z') || (*arg)[j] == '_')
		j++;
	i = ft_strlen(start) + (ft_strlen(*arg) - j);
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return ;
	l = 0;
	while (l < i && start[l])
	{
		ptr[l] = start[l];
		l++;
	}
	while (l < i && (*arg)[j])
		ptr[l++] = (*arg)[j++];
	ptr[l] = '\0';
	free((*arg));
	(*arg) = ptr;
}

void	remake_token(char **arg, char *start, char *var, int j)
{
	int		i;
	int		l;
	int		m;
	char	*ptr;

	j++;
	while (((*arg)[j] >= '0' && (*arg)[j] <= '9')
		|| ((*arg)[j] >= 'a' && (*arg)[j] <= 'z')
		|| ((*arg)[j] >= 'A' && (*arg)[j] <= 'Z') || (*arg)[j] == '_')
		j++;
	i = ft_strlen(start) + ft_strlen(var) + (ft_strlen(*arg) - j);
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return ;
	l = -1;
	while (++l < i && start[l])
		ptr[l] = start[l];
	m = 0;
	while (l < i && var[m])
		ptr[l++] = var[m++];
	while (l < i && (*arg)[j])
		ptr[l++] = (*arg)[j++];
	ptr[l] = '\0';
	free((*arg));
	(*arg) = ptr;
}
