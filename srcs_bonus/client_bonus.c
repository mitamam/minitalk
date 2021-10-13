/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:17:48 by mmasuda           #+#    #+#             */
/*   Updated: 2021/10/13 14:30:16 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/client_bonus.h"

void	check_argument_is_valid(const pid_t pid, const char *to_send_msg)
{
	size_t	msg_length;

	if (pid <= 1)
		display_error(INVALID_PID, pid, "client");
	msg_length = ft_strlen(to_send_msg);
	if (msg_length > 50000)
		display_error(MSG_TOO_LONG, NONE, "client");
}

void	send_char_to_server(const pid_t pid, const char to_send)
{
	int	bit;
	int	i;

	i = 7;
	while (i >= 0)
	{
		usleep(INTERVAL);
		bit = (to_send >> i) & 0x01;
		if (kill(pid, SIGUSR1 + bit) == -1)
			display_error(SEND_ERROR, NONE, "client");
		i--;
	}
}

void	send_message_to_server(const pid_t pid, const char *to_send_msg)
{
	size_t	i;

	i = -1;
	while (*to_send_msg != '\0')
	{
		send_char_to_server(pid, *to_send_msg);
		to_send_msg++;
	}
	send_char_to_server(pid, EOT);
}

void	signal_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (sig == SIGUSR1)
	{
		ft_printf("./client: success signal received from server.\n");
		exit(SUCCESS);
	}
	else if (sig == SIGUSR2)
		display_error(ERROR_ON_SERVER, NONE, "client");
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	pid_t				pid;
	char				*to_send_msg;

	if (argc != 3)
		display_error(INCORRECT_ARG, 0, "client");
	pid = ft_atoi(argv[1]);
	to_send_msg = argv[2];
	check_argument_is_valid(pid, to_send_msg);
	ft_memset(&act, 0, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = &signal_handler;
	if (sigaction(SIGUSR1, &act, NULL))
		display_error(SIGACTION_ERROR, pid, "client");
	if (sigaction(SIGUSR2, &act, NULL))
		display_error(SIGACTION_ERROR, pid, "client");
	send_message_to_server(pid, to_send_msg);
	while (1)
		pause();
	return (0);
}
