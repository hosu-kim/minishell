/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:42:24 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 15:05:11 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

static int	process_path_segment(char **paths, char *path, int *count,
		int *range)
{
	paths[*count] = extract_path_segment(path, range[0], range[1]);
	if (!paths[*count])
	{
		free_paths(paths);
		return (0);
	}
	(*count)++;
	return (1);
}

static int	process_colon_segments(char **paths, char *path, int *count)
{
	int	i;
	int	start;
	int	range[2];

	i = 0;
	start = 0;
	while (path[i])
	{
		if (path[i] == ':')
		{
			range[0] = start;
			range[1] = i;
			if (!process_path_segment(paths, path, count, range))
				return (0);
			start = i + 1;
		}
		i++;
	}
	range[0] = start;
	range[1] = i;
	return (process_path_segment(paths, path, count, range));
}

char	**ft_split_path(char *path)
{
	char	**paths;
	int		count;
	int		segment_count;

	if (!path)
		return (NULL);
	count = count_paths(path);
	paths = malloc(sizeof(char *) * (count + 1));
	if (!paths)
		return (NULL);
	segment_count = 0;
	if (!process_colon_segments(paths, path, &segment_count))
		return (NULL);
	paths[segment_count] = NULL;
	return (paths);
}
