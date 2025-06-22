/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaandras <jaandras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:02:55 by jakand            #+#    #+#             */
/*   Updated: 2025/06/22 22:00:46 by jaandras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <minishell.h>

typedef struct s_cmd_token	t_cmd_token;

int		find_var_end(char *arg, int start);
char	*start_of_env(char *arg);
char	*extract_var_name(char *arg, int start, int end);
int		make_env(t_cmd_token **token, int i, int j, int exit_status);
void	expand_token(t_cmd_token *token, int exit_status);
char	*get_variable_value(char *env, int exit_status);
void	process_token_args(t_cmd_token *token, int exit_status);
void	update_token(char **arg, char *start, int j);
void	remake_token(char **arg, char *start, char *var, int j);
char	*ft_itoa(int n);

#endif
