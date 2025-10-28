# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 13:01:19 by sdossa            #+#    #+#              #
#    Updated: 2025/10/20 04:37:32 by sdossa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#****************************************************************#
#                             NAMES                              #
#****************************************************************#

NAME 		= minishell

#****************************************************************#
#                     COMPILATION AND OPTIONS                    #
#****************************************************************#

LIBFT 		= ./libft/libft.a
LIBS 		= -lreadline

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror $(INCLUDES)
RM 			= rm -f
MKDIR 		= mkdir -p
INCLUDES	= -I includes -I libft

#****************************************************************#
#                          SOURCE FILES                          #
#****************************************************************#

SRCS_DIR	= srcs
SRCS 		= $(shell find $(SRCS_DIR) -name "*.c")


#****************************************************************#
#                          OBJECT FILES                          #
#****************************************************************#

OBJ_DIR 	= obj
OBJS 		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)


#****************************************************************#
#                               RULES                            #
#****************************************************************#

GREEN		= \033[32m
YELLOW		= \033[33m
RED			= \033[31m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) created successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "$(MAGENTA)Compiling $<...$(RESET)"
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

#****************************************************************#
#                         CLEANING RULES                         #
#****************************************************************#

clean:
		@echo "$(YELLOW)Cleaning object files...$(RESET)"
		$(RM) -r $(OBJ_DIR)
		make clean -C ./libft

fclean: clean
		@echo "$(RED)Cleaning $(NAME)...$(RESET)"
		$(RM) $(NAME)
		make fclean -C ./libft


re: fclean all

norm:
	@echo "$(BLUE)Checking norminette...$(RESET)"
	@norminette $(SRCS_DIR) includes

.PHONY: all clean fclean re

