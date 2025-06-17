/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:14:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/17 17:48:57 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

static void	init_shell(t_shell *shell)
{
	shell->
}

#ifdef DEBUG
void	print_parsed_token(t_cmd_token *print_tok)
{
	t_redirection	*print_redir;
	int	i;

	while (print_tok)
		{
			i = 0;
			printf("pipe %i\n", print_tok->has_pipe);
			while (print_tok->cmd_with_args[i])
			{
				printf("argument[%i]: %s quotes type: %i\n", i, print_tok->cmd_with_args[i], print_tok->arg_types[i]);
				i++;
			}
			print_redir = print_tok->input_redirs;
			while (print_redir)
			{
				printf("input type: %d value: %s quotes type: %i\n", print_redir->type, print_redir->target, print_redir->target_types);
				print_redir = print_redir->next;
			}
			print_redir = print_tok->output_redirs;
			while (print_redir)
			{
				printf("output type: %d value: %s quotes type: %i\n", print_redir->type, print_redir->target, print_redir->target_types);
				print_redir = print_redir->next;
			}
			printf("next\n");
			print_tok = print_tok->next_cmd_token;
		}
}
#endif

int	main(void)
{
	t_token		*token;
	t_cmd_token	*token_parsed;
	t_cmd_token	*print_tok;
	char		*line;
	pid_t	pid = fork();

	init_parent_signals();
	while (1)
	{
		if (g_received_signal == SIGINT)
		{
			rl_replace_line("", 0);
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
			g_received_signal = 0;
		}
		else if (g_received_signal == SIGQUIT)
			g_received_signal = 0;
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		token = tokenizer(line);
		if (token == NULL)
		{
			free(line);
			continue ;
		}
		token_parsed = parser(token);
		if (token_parsed == NULL)
		{
			free_token(token);
			free(line);
			continue ;
		}
		print_tok = token_parsed;
		print_parsed_token(print_tok);
		expand_token(token_parsed);
		print_parsed_token(print_tok);

		if (pid < 0)
			perror("fork");
		else if (pid == 0)
		{
			init_child_signals();
			execve(token_parsed->cmd_with_args[0],
								token_parsed->cmd_with_args,
								environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, NULL, 0);
		free_token(token);
		free(line);
		free_token_parsed(token_parsed);
	}
	return (0);
}
