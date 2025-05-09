/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:23:13 by hoskim            #+#    #+#             */
/*   Updated: 2025/05/09 22:24:50 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
Things to Implement:
1. Handle ' (single quote which should prevent the shell
   from interpreting the meta-characters in the quoted sequence.
2. Handle " (double quote) which should prevent the shell from interpreting
   the meta-char
3. Handle environment variables ($ followed by a sequence of characters) which
   should expand to their values.
4. Handle $? which should expand to the exit status of the most recently executed
   foreground pipeline.
...from the PDF
*/