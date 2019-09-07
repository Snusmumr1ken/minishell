##########################################################
#                                                        #
#             Makefile is created by anyvchyk            #
#                  for minishell project                 #
#                                                        #
##########################################################

#############           Varaibles            #############
#                                                        #
FILES = main parse_command no_warranty custom_split \
        cd pwd echo launch_proc init usefull \
        create_pathes env setenv setenv2\

SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addsuffix .o, $(FILES))

LIBFT = ./libft/libft.a

NAME = minishell

FLAGS = -Wall -Wextra -Werror
#                                                        #
##########################################################

#############              Rules             #############
#                                                        #
all: $(NAME)

.PHONY: all clean
.NOTPARALLEL: all clean fclean re

$(NAME): $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ): $(LIBFT) $(SRC)
	@gcc -c $(FLAGS) $(SRC)

$(LIBFT):
	@make -C ./libft

libft_clean:
	@make -C ./libft clean

libft_fclean:
	@make -C ./libft fclean

clean: libft_clean
	@rm -rf $(OBJ)

fclean: libft_fclean
	@rm -rf $(OBJ)
	@rm -rf $(NAME)

re: fclean all
#                                                        #
##########################################################
