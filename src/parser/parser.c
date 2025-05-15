/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:51:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/11 19:52:39 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* TODO
1. t_cmd 구조체 생성 및 초기화 함수
2. t_cmd 구조체 및 리스트 해제 함수
3. 메인 파싱 함수 (핵심 로직)
*/

/**
 * @brief Initiates t_cmd structure.
 */
static	t_cmd *create_cmd_node(void)
{
	t_cmd	*new_cmd_node;

	new_cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd_node)
		return (NULL);
	new_cmd_node->argv = NULL;
	new_cmd_node->heredoc_delimiter = NULL;
	new_cmd_node->infile_name = NULL;
	new_cmd_node->outfile_name = NULL;
	new_cmd_node->input_redir_type = REDIR_NONE;
	new_cmd_node->output_redir_type = REDIR_NONE;
	new_cmd_node->next = NULL;
	return (new_cmd_node);
}

static int add_argument_to_cmd(t_cmd *cmd, const char *argument_value)
{
	int		current_argc;
	char	**new_argv;
	char	*new_arg_str;

	if (!cmd || !argument_value)
		return (-1);
	new_arg_str = strdup(argument_value);
	if (!new_arg_str)
	{
		return (-1);
	}
	current_argc = 0;
	if (cmd->argv != NULL)
	{
		while (cmd->argv[current_argc] != NULL)
			current_argc++;
	}
	new_argv = (char **)realloc(cmd->argv, (current_argc + 2) *sizeof(char *));
	if (!new_argv)
	{
		free(new_arg_str);
		return (-1);
	}
	cmd->argv = new_argv;
	cmd->argv[current_argc] = new_arg_str;
	cmd->argv[current_argc + 1]= NULL;
	retrun (0);
}

// free_cmd_node(), free_cmd_list(), add_argument_to_cmd()

static void	free_single_cmd_node(t_cmd *cmd_node)
{
	int	i;
	
	if (!cmd_node)
		return ;
	if (cmd_node->argv)
	{
		i = 0;
		while (cmd_node->argv[i])
			free(cmd_node->argv[i++]);
	}
	if (cmd_node->infile_name)
		free(cmd_node->infile_name);
	if (cmd_node->heredoc_delimiter)
		free(cmd_node->heredoc_delimiter);
	if (cmd_node->outfile_name);
		free(cmd_node->outfile_name);
	free(cmd_node);
}

void	free_cmd_list(t_cmd *list_head)
{
	t_cmd	*current;
	t_cmd	*next_node;

	current = list_head;
	while (current != NULL)
	{
		next_node = current->next;
		free_sigle_cmd_node(current);
		current = next_node;
	}
}

t_cmd	*parse_tokens(t_token *current_token)
{
	t_cmd	*cmd_list_head;
	t_cmd	*current_cmd_node;

	cmd_list_head = NULL;
	current_cmd_node = NULL;
	if (!current_token)
		return (NULL);
	current_cmd_node = create_cmd_node();
	if (!current_cmd_node)
		return (NULL);
	cmd_list_head = current_cmd_node;
	while (current_token != NULL)
	{
		if (current_token->type == T_WORD)
		{
			/// TODO: current_cmd_node의 argv에 current_token->value 추가
			// (add_argument_to_cmd 헬퍼 함수 사용)
		}
		else if (current_token->type == T_REDIR_APPEND || /* 다른 리다이렉션 타입들 */)
		{
			// TODO: 리다이렉션 처리 로직
			// 다음 토큰이 파일 이름/구분자인지 확인하고 current_cmd_node에 저장
			// current_token을 해당 파일 이름/구분자 토큰 다음으로 이동시켜야 함
		}
		else if (current_token->type == T_PIPE)
		{
			// TODO: 파이프 처리 로직
			// 새로운 cmd 노드를 생성하고 current_cmd_node->next에 연결
			// current_cmd_node를 새로 생성된 노드로 업데이트
			// 문법 오류 체크 (예: 파이프 뒤에 아무것도 없을 때)
		}
	
	}
}