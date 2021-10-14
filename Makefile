# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 12:16:13 by mmasuda           #+#    #+#              #
#    Updated: 2021/10/13 23:12:37 by mmasuda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minitalk
C_NAME := client
S_NAME := server

C_SRCS := srcs/client.c srcs/utils.c
S_SRCS := srcs/server.c srcs/utils.c

C_BONUS_SRCS := srcs_bonus/client_bonus.c srcs_bonus/utils_bonus.c
S_BONUS_SRCS := srcs_bonus/server_bonus.c srcs_bonus/utils_bonus.c

C_BONUS_OBJS := $(C_BONUS_SRCS:%.c=%.o)
S_BONUS_OBJS := $(S_BONUS_SRCS:%.c=%.o)

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

PRINTF_DIR := ./ft_printf
PRINTF := $(PRINTF_DIR)/libftprintf.a

CC := gcc
CFLAGS := -Wall -Wextra -Werror

RM := rm -f

ifdef WITH_BONUS
	C_OBJS := $(C_BONUS_OBJS)
	S_OBJS := $(S_BONUS_OBJS)
else
	C_OBJS := $(C_SRCS:%.c=%.o)
	S_OBJS := $(S_SRCS:%.c=%.o)
endif

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(C_NAME) $(S_NAME)

$(C_NAME): $(C_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(C_OBJS) $(LIBFT) $(PRINTF) -o $@

$(S_NAME): $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) $(LIBFT) $(PRINTF) -o $@

all: $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)
	$(RM) $(C_OBJS) $(S_OBJS) $(C_BONUS_OBJS) $(S_BONUS_OBJS)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)
	$(RM) $(C_OBJS) $(S_OBJS) $(C_BONUS_OBJS) $(S_BONUS_OBJS)
	$(RM) $(C_NAME) $(S_NAME)

re: fclean all

bonus:
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re