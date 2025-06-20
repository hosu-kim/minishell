/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:42:24 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/20 19:17:06 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static void	copy_substring(char *dest, const char *src, int len)
{
	int	i;

	i = 0;
	while (i < len && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	count_paths(char *path)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	return (count);
}

static char	*extract_path_segment(char *path, int start, int end)
{
	char	*segment;
	int		len;

	len = end - start;
	segment = malloc(len + 1);
	if (!segment)
		return (NULL);
	copy_substring(segment, &path[start], len);
	return (segment);
}

char	**ft_split_path(char *path)
{
	char	**paths;
	int		count;
	int		i;
	int		start;

	if (!path)
		return (NULL);
	count = count_paths(path);
	paths = malloc(sizeof(char *) * (count + 1));
	if (!paths)
		return (NULL);
	i = 0;
	count = 0;
	start = 0;
	while (path[i])
	{
		if (path[i] == ':')
		{
			paths[count] = extract_path_segment(path, start, i);
			if (!paths[count])
			{
				free_paths(paths);
				return (NULL);
			}
			count++;
			start = i + 1;
		}
		i++;
	}
	paths[count] = extract_path_segment(path, start, i);
	if (!paths[count])
	{
		free_paths(paths);
		return (NULL);
	}
	paths[count + 1] = NULL;
	return (paths);
}
