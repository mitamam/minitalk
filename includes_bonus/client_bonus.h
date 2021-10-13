/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:17:34 by mmasuda           #+#    #+#             */
/*   Updated: 2021/10/13 14:16:09 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_BONUS_H
# define CLIENT_BONUS_H

# include "minitalk_bonus.h"

void	signal_handler(int sig, siginfo_t *siginfo, void *context);
void	send_message_to_server(const pid_t pid, const char *to_send_msg);
void	send_char_to_server(const pid_t pid, const char to_send);
void	check_argument_is_valid(const pid_t pid, const char *to_send_msg);

#endif
