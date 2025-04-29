/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:44:56 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/29 17:45:28 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

// include/builtin.h
bool	is_builtin(const char *cmd);
int		run_builtin(t_cmd *cmd, char ***envp);

/* individual commands */
int		builtin_cd(t_cmd *cmd, char ***envp);
int		builtin_echo(t_cmd *cmd, char ***envp);
/* … */