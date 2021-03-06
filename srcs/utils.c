/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:22:51 by mmasuda           #+#    #+#             */
/*   Updated: 2021/10/13 23:43:19 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_signal_pid;

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

t_bool	is_caller_server(const char *caller)
{
	int	result;

	result = ft_strncmp(caller, "server", ft_strlen("server"));
	if (result == 0)
		return (true);
	else
		return (false);
}

void	display_error(const int error, const pid_t pid, const char *caller)
{
	if (error == INCORRECT_ARG)
		ft_printf("usage: ./%s [pid] [message]\n", caller);
	else if (error == INVALID_PID)
		ft_printf("./%s: invalid pid: %d\n", caller, pid);
	else if (error == MSG_TOO_LONG)
		ft_printf("./%s: message too long\n", caller);
	else if (error == SIGACTION_ERROR)
		ft_printf("./%s: an error has occurred with sigaction.\n", caller);
	else if (error == ERROR_ON_SERVER)
		ft_printf("./%s: an error has occurred on the server.\n", caller);
	else if (error == SEND_ERROR)
		ft_printf("./%s: failed to send signal.\n", caller);
	if (is_caller_server(caller))
		send_signal_to_client(ERROR);
	exit(ERROR);
}
