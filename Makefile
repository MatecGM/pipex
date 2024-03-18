NAME = pipex

CC = cc
#FLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj

SRC = main.c \
	command_access.c \
	ft_split_quote.c \
	read_file.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m

LIBFT = libft/libft.a

all : $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	@echo "$(GREEN)$(NAME) compilation successful !$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(FLAGS) -g -I include -I libft -o $@ -c $<

$(LIBFT):
	@echo "$(PURPLE)Compiling LIBFT...$(NC)"
	@make -C libft -j -s

clean:
	@echo "$(RED)Removing object...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Removing libft...$(NC)"
	@make -C libft clean -s

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make -C libft fclean -s

re: fclean all

.PHONY: all clean fclean re bonus