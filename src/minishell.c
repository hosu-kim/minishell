/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:14:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/06/09 15:08:33 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "expander/expander.h"


/**
 * Entry point for the minishell program.
 * Sets up signal handlers, initializes environment list,
 * then enters the main read-eval-print loop.
 */

void	free_redirections(t_redirection *redir)
{
	t_redirection	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		if (temp->target)
			free(temp->target);
		free(temp);
	}
}

void	free_token_parsed(t_cmd_token *token_parsed)
{
	int		i;
	t_cmd_token	*temp;

	while (token_parsed)
	{
		temp = token_parsed;
		token_parsed = token_parsed->next_cmd_token;
		if (temp->cmd_with_args)
		{
			i = 0;
			while (temp->cmd_with_args[i])
			{
				free(temp->cmd_with_args[i]);
				i++;
			}
			free(temp->cmd_with_args);
		}
		if (temp->arg_types)
			free(temp->arg_types);
		if (temp->input_redirs)
			free_redirections(temp->input_redirs);
		if (temp->output_redirs)
			free_redirections(temp->output_redirs);
		free(temp);
	}
}

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

int	main(void)
{
	t_token		*token;
	t_cmd_token	*token_parsed;
	t_cmd_token	*print_tok;
	char		*line;

	while (1)
	{
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
			if (token)
				free_token(token);
			if (line)
				free(line);
			continue ;
		}
		print_tok = token_parsed;

		print_parsed_token(print_tok);

		expand_token(token_parsed);

		print_parsed_token(print_tok);

		if (token)
			free_token(token);
		if (line)
			free(line);
		if (token_parsed)
			free_token_parsed(token_parsed);
		// parsing and execution logics
	}
	return (0);
}
