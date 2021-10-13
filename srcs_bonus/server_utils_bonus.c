/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 23:35:27 by mmasuda           #+#    #+#             */
/*   Updated: 2021/10/13 14:29:38 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/server_bonus.h"

void	output_recived_message(char *recived_msg, const int current_msg_length)
{
	write(1, recived_msg, current_msg_length);
	write(1, "\n", 1);
	ft_memset(recived_msg, 0, BUFFER_SIZE + 1);
	send_signal_to_client(SUCCESS);
}
