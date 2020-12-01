NAME = minishell
HEADERS = ./parser/parser.h
CFLAGS = -g -Wall -Werror -Wextra

SRC = main.c parser/wait_str.c parser/create_lst.c parser/add_lst.c\
	parser/split_words1.c parser/free_cmd.c parser/split_words2.c \
	parser/record_redir.c mini/ft_env.c parser/give_directory.c\
	mini/ft_give_export.c mini/ft_give_unset.c mini/ft_give_pwd_env.c\
	mini/ft_utils.c mini/ft_start.c mini/ft_give_command.c mini/ft_give_cd.c\
	mini/ft_give_echo.c parser/utils.c mini/ft_utils2.c parser/split_words3.c\
	mini/ft_exit.c

OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft all
	gcc $(OBJ) ./libft/libft.a -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean:	clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re:		fclean all

bonus: all

norm: 
	norminette parser/*.c libft/*.c libft/*.h mini/*.c main.c minishell.h
npars:
	norminette parser/*.c

.PHONY: all clean fclean re bonus norm npars