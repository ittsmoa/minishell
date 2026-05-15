NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/main.c \
      src/executor/executor.c \
      src/exec_external.c \
      src/executor/get_cmd_path.c \
      src/executor/is_builtin.c \
      src/executor/execute_builtin.c \
      src/builtins/builtin_pwd.c \
      src/builtins/builtin_echo.c \
      src/builtins/builtin_env.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re