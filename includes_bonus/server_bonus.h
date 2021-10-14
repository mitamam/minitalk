/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:34:58 by mmasuda           #+#    #+#             */
/*   Updated: 2021/10/13 23:03:34 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H

# include "minitalk_bonus.h"

void	signal_handler(int sig, siginfo_t *siginfo, void *context);
void	convert_bit_into_string(const int sig);
void	convert_signal_into_bit(const int sig, int *stored_bits,
			const int number_of_bits);
void	output_recived_message(char *recived_msg, const int current_msg_length);

#endif
