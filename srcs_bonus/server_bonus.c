/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:18:31 by mmasuda           #+#    #+#             */
/*   Updated: 2021/10/13 14:36:44 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/server_bonus.h"

void	send_signal_to_client(int state)
{
	if (state == SUCCESS)
	{
		if (kill(g_signal_pid, SIGUSR1) == -1)
			display_error(SEND_ERROR, NONE, "server");
	}
	else if (state == ERROR)
	{
		if (kill(g_signal_pid, SIGUSR2) == -1)
			display_error(SEND_ERROR, NONE, "server");
	}
}

void	convert_signal_into_bit(const int sig, int *stored_bits,
	const int number_of_bits)
{
	if (sig == SIGUSR2)
		*stored_bits += 1;
	if (number_of_bits + 1 <= 7)
		*stored_bits <<= 1;
}

void	convert_bit_into_string(const int sig)
{
	char		recived_msg[BUFFER_SIZE + 1];
	static int	stored_bits;
	static int	number_of_bits;
	static int	current_msg_length;

	if (number_of_bits <= 7)
	{
		convert_signal_into_bit(sig, &stored_bits, number_of_bits);
		number_of_bits++;
	}
	if (number_of_bits >= 8)
	{
		recived_msg[current_msg_length] = stored_bits;
		if (recived_msg[current_msg_length] == EOT)
			output_recived_message(recived_msg, current_msg_length);
		current_msg_length++;
		stored_bits = 0;
		number_of_bits = 0;
	}
}

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;
	g_signal_pid = siginfo->si_pid;
	convert_bit_into_string(sig);
}

int	main(void)
{
	struct sigaction	act;
	pid_t				pid;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	ft_memset(&act, 0, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		display_error(SIGACTION_ERROR, NONE, "server");
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		display_error(SIGACTION_ERROR, NONE, "server");
	while (1)
		pause();
	return (0);
}
