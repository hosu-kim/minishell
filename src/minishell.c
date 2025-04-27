/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/27 22:49:52 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static char	*dup_env(char *envp[])
{
	int		i;
	int		cnt;
	char	**new;

	while (envp[cnt])
		cnt++;
	new = malloc(sizeof(char *) * (cnt + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < cnt)
	{
		new[i] = strdup(envp[i]);
		i++;
	}
	new[cnt] = NULL;
	return (new);
}

static void	free_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	minishell_init(t_shell *shell, char *envp[])
{
	shell->last_exit_status = 0;
	shell->envp = dup_env(envp);
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	minishell_cleanup(t_shell *shell)
{
	free_env(shell->envp);
	rl_clear_history();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		shell;
	t_command	*cmd_list;
	char		*input;

	(void)argc;
	(void)argv;
	minishell_init(&shell, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		cmd_list = parse_input(input);
		free(input);
		if (cmd_list)
		{
			execute_command(&shell, cmd_list);
			free_command(cmd_list);
		}
	}
	minishell_cleanup(&shell);
	return (0);
}

