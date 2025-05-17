/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:14:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/17 16:17:45 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
# include "lexer/lexer.h"


/**
 * Entry point for the minishell program.
 * Sets up signal handlers, initializes environment list,
 * then enters the main read-eval-print loop.
 */

int	main(void)
{
	t_token	*token;
	t_token *print_tok;
	char	*line;
	// char	*cwd;

	while (1)
	{
		// cwd = getcwd(NULL, 0); // used to implement pwd
		// printf("%s", cwd);
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		token = tokenize(line);
		print_tok = token;
		while (print_tok)
		{
			printf("token type: %d and value: %s\n", print_tok->type, print_tok->value);
			print_tok = print_tok->next;
		}
		if (token)
			free_token(token);
		if (line)
			free(line);
		// parsing and execution logics
		// free_tokens(token);
	}
	return (0);
}
