/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:18:14 by jakand            #+#    #+#             */
/*   Updated: 2025/06/14 14:18:19 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// include/builtin.h
bool	is_builtin(const char *cmd);
int		run_builtin(t_cmd *cmd, char ***envp);

/* individual commands */
int		builtin_cd(t_cmd *cmd, char ***envp);
int		builtin_echo(t_cmd *cmd, char ***envp);
/* … */