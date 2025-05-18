/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:14:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/18 23:04:36 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
# include "lexer/lexer.h"
# include "parser/parser.h"


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

void	free_token_parsed(t_command *token_parsed)
{
	int		i;
	t_command	*temp;

	while (token_parsed)
	{
		temp = token_parsed;
		token_parsed = token_parsed->next;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		if (temp->input_redir)
			free_redirections(temp->input_redir);
		if (temp->output_redir)
			free_redirections(temp->output_redir);
		free(temp);
	}
}

int	main(void)
{
	t_token		*token;
	t_command	*token_parsed;
	t_command	*print_tok;
	t_redirection	*print_redir;
	char		*line;
	int			i;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		token = tokenize(line);
		token_parsed = parser(token);
		print_tok = token_parsed;
		while (print_tok)
		{
			i = 0;
			while (print_tok->args[i])
			{
				printf("value: %s\n", print_tok->args[i]);
				i++;
			}
			printf("next\n");
			print_redir = print_tok->input_redir;
			while (print_redir)
			{
				printf("type: %d value: %s\n", print_redir->type, print_redir->target);
				print_redir = print_redir->next;
			}
			print_tok = print_tok->next;
		}
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
