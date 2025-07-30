# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmatthes <rmatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 12:49:05 by rmatthes          #+#    #+#              #
#    Updated: 2025/07/30 13:19:18 by rmatthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCDIR = SCR
OBJDIR = OBJ

SRCS = main.c \
	utils.c \
	mutex.c \
	init.c \
	monitor.c \
	philo.c

SRC_PATHS = $(addprefix $(SRCDIR)/, $(SRCS))
OBJ_NAMES = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJDIR)/, $(OBJ_NAMES))

CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile source files to OBJ/*.o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
