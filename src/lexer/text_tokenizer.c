/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:30:02 by jakand            #+#    #+#             */
/*   Updated: 2025/06/21 11:45:40 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	calculate_word_length(const char **input, int *sq, int *dq)
{
	int	pos;
	int	total_len;

	pos = 0;
	total_len = 0;
	while (pos < (int)ft_strlen(*input) && !is_word_boundary((*input)[pos]))
	{
		if (!process_quote_char(input, &pos, &total_len, sq, dq))
			return (-1);
	}
	return (total_len);
}

static void	extract_quote_content(const char **input, int *pos, char **temp_pos, char quote_char)
{
	(*pos)++;
	while (*pos < (int)ft_strlen(*input) && (*input)[*pos] != quote_char 
		&& (*input)[*pos] != '\0')
		*(*temp_pos)++ = (*input)[(*pos)++];
	if ((*input)[*pos] == quote_char)
		(*pos)++;
}

static char	*extract_word(const char **input, int total_len)
{
	char	*word_value;
	char	*temp_pos;
	int		pos;

	word_value = malloc((total_len + 1) * sizeof(char));
	if (!word_value)
		return (NULL);
	pos = 0;
	temp_pos = word_value;
	while (pos < (int)ft_strlen(*input) && !is_word_boundary((*input)[pos]))
	{
		if ((*input)[pos] == '\'' || (*input)[pos] == '"')
			extract_quote_content(input, &pos, &temp_pos, (*input)[pos]);
		else
			*temp_pos++ = (*input)[pos++];
	}
	*temp_pos = '\0';
	*input += pos;
	return (word_value);
}

static void	set_token_type(t_token *new_node, int has_single_quotes, int has_double_quotes)
{
	if (has_single_quotes && !has_double_quotes)
		new_node->type = T_Q_WORD;
	else if (has_double_quotes && !has_single_quotes)
		new_node->type = T_D_Q_WORD;
	else if (has_single_quotes && has_double_quotes)
		new_node->type = T_D_Q_WORD;
	else
		new_node->type = T_WORD;
}

int	text_tokenizer(const char **input, t_token *new_node)
{
	int		has_single_quotes;
	int		has_double_quotes;
	int		total_len;
	char	*word_value;

	has_single_quotes = 0;
	has_double_quotes = 0;
	total_len = calculate_word_length(input, &has_single_quotes, 
			&has_double_quotes);
	if (total_len <= 0)
		return (FAILURE);
	word_value = extract_word(input, total_len);
	if (!word_value)
		return (FAILURE);
	set_token_type(new_node, has_single_quotes, has_double_quotes);
	new_node->value = word_value;
	new_node->next = NULL;
	return (YES);
}
