NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/main.c \
      src/signals.c \
      src/signal_modes.c \
      src/executor/executor.c \
      src/exec_external.c \
      src/executor/get_cmd_path.c \
      src/executor/is_builtin.c \
      src/executor/execute_builtin.c \
      src/executor/execute_pipeline.c \
      src/executor/pipeline_child.c \
      src/executor/pipeline_utils.c \
      src/executor/pipeline_status.c \
      src/executor/execution_status.c \
      src/executor/command_redirection.c \
      src/executor/prepare_redirections.c \
      src/executor/heredoc.c \
      src/executor/heredoc_utils.c \
      src/builtins/builtin_pwd.c \
      src/builtins/builtin_echo.c \
      src/builtins/builtin_env.c \
      src/env/copy_envp.c \
      src/env/env_get.c \
      src/env/env_set.c \
      src/builtins/builtin_cd.c \
      src/env/env_add.c \
      src/builtins/builtin_export.c \
      src/builtins/builtin_export_print.c \
      src/env/env_remove.c \
      src/builtins/builtin_unset.c \
      src/builtins/builtin_exit.c \
      src/builtins/builtin_exit_parse.c \
      parser/lexer.c \
      parser/utilities_1.c \
      parser/validation.c \
      parser/utilities_2.c \
      parser/utilities3.c \
      parser/parsing.c \
      parser/parsing_helper.c \
      parser/parsing_helper2.c \
      parser/parsing_helper3.c \
      parser/parser_validation.c \
      parser/expander_env.c \
      parser/expander_split.c \
      parser/expander_utilities.c \
      parser/expander_utilities2.c \
      parser/expander.c 

OBJ = $(SRC:.c=.o)
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
