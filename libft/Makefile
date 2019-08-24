#######################################################################
#                                                                     #
#                    Makefile is created by anyvchyk                  #
#                        for LIBFT V2.0 project                       #
#                                                                     #
#######################################################################

###############               Varaibles                  ##############
#                                                                     #
LIBFT_FUNC	= get_next_line ft_memmove ft_memcpy ft_abs ft_atoi \
			  ft_sqrt ft_strcat ft_strchr ft_strclr ft_strcmp \
			  ft_strcpy ft_strdup ft_strsub ft_strncmp ft_strjoin \

PRINTF_FUNC	= ft_printf ftoa manage_binary manage_char manage_decimal \
			  manage_float manage_hex manage_octal manage_percent \
			  manage_pointer manage_string manage_unsigned \
			  useful_functions work_with_format work_with_format2 

LIBFT_SRC = $(addprefix src/, $(addsuffix .c, $(LIBFT_FUNC)))
LIBFT_OBJ = $(addprefix src/, $(addsuffix .o, $(LIBFT_FUNC)))

PRINTF_SRC = $(addprefix ft_printf/, $(addsuffix .c, $(PRINTF_FUNC)))
PRINTF_OBJ = $(addprefix ft_printf/, $(addsuffix .o, $(PRINTF_FUNC)))

INC = -I./includes -I./ft_printf
LIBFT_HEADER = ./includes/libft.h
PRINTF_HEADER = ./ft_printf/libp.h

NAME	= libft.a

FLAGS	= -Wall -Wextra -Werror
#                                                                     #
#######################################################################

###############                  Rules                 ################
#                                                                     #
all: $(NAME)

.PHONY: all clean
.NOTPARALLEL: all $(NAME) clean fclean re

$(NAME): $(LIBFT_OBJ) $(PRINTF_OBJ) $(LIBFT_HEADER) $(PRINTF_HEADER)
	@ar rcs $(NAME) $(LIBFT_OBJ) $(PRINTF_OBJ)	

$(LIBFT_OBJ): src/%.o : src/%.c $(LIBFT_HEADER)
	@gcc -o $@ $(FLAGS) $(INC) -c $<

$(PRINTF_OBJ): ft_printf/%.o : ft_printf/%.c $(PRINTF_HEADER)
	@gcc -o $@ $(FLAGS) $(INC) -c $<

clean:
	@rm -rf $(LIBFT_OBJ) $(PRINTF_OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
#                                                                      #
########################################################################
