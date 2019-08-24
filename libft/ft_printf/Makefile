######################################################
#                                                    #
#         Makefile is created by anyvchyk            #
#                for printf project                  #
#                                                    #
######################################################

##########           Varaibles              ##########
#                                                    #
SRC		=   ft_printf.c useful_functions.c\
            work_with_format.c work_with_format2.c \
            manage_char.c manage_string.c \
            manage_pointer.c manage_decimal.c \
            manage_unsigned.c manage_octal.c \
            manage_binary.c manage_hex.c \
            manage_percent.c manage_float.c ftoa.c

OBJ		= $(SRC:.c=.o)

NAME	= libprintf.a
#                                                     #
#######################################################

##########               Rules               ##########
#                                                     #
all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

$(OBJ): $(SRC)
	@gcc -Wall -Wextra -Werror -c $(SRC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
#                                                     #
#######################################################
