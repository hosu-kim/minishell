/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:38:18 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/21 11:36:57 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

/* String utility functions */
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);

/* Path utility functions */
char	**ft_split_path(char *path);
void	free_paths(char **paths);
char	*find_executable(char *cmd);
void	my_execvp(char *cmd, char **args, char **env);
char	*extract_path_segment(char *path, int start, int end);

/* Character utility functions */
int		is_valid_var_char(char c);
void	free_var(char **env, char **var);

#endif
