/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:17:46 by mmasuda           #+#    #+#             */
/*   Updated: 2021/10/13 14:15:21 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define SUCCESS 0
# define ERROR 1
# define BUFFER_SIZE 50000
# define INTERVAL 100
# define EOT 0x04
# define NONE 0

extern int	g_signal_pid;

typedef enum e_errors
{
	INCORRECT_ARG,
	INVALID_PID,
	MSG_TOO_LONG,
	SIGACTION_ERROR,
	ERROR_ON_SERVER,
	SEND_ERROR,
}	t_errors;

void	display_error(const int error, const pid_t pid, const char *caller);

#endif
