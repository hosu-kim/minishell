/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:55:55 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/22 15:26:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <limits.h>

# define PATH_MAX 4096

int		builtin_echo(char **args);
int		builtin_cd(char **args, char ***env);
int		builtin_pwd(void);
int		builtin_export(char **args, char ***env);
int		builtin_unset(char **args, char ***env);
int		builtin_exit(char **args);
int		builtin_env(char **env);

/* Builtin utility functions */
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd_token *cmd, char ***envp);
char	*get_env_value(char *key, char **env);
int		count_env_vars(char **env);
char	**add_env_var(char **env, char *key, char *value);
int		builtin_exit(char **args);

/* Export utility functions */
int		is_valid_identifier(const char *str);
char	*extract_key(char *arg, char *address_of_equal_sign);
int		handle_export_error(char *arg);
int		handle_export_with_value(char *arg, char *equal_sign, char ***env);
int		handle_export_without_value(char *arg, char ***env);

#endif