# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/03 11:06:26 by yalabidi     #+#   ##    ##    #+#        #
#    Updated: 2019/04/30 16:10:15 by matheme     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME		= libft.a

HEADER		= libft.h
SRC_PATH	= .
SRC_NAME	= ft_memcpy.c\
			  ft_strncat.c\
			  ft_memmove.c\
			  ft_memset.c\
			  ft_strcpy.c\
			  ft_strncpy.c\
			  ft_bzero.c\
			  ft_memccpy.c\
			  ft_strdup.c\
			  ft_memchr.c\
			  ft_strlcat.c\
			  ft_memcmp.c\
			  ft_strcat.c\
			  ft_strlen.c\
			  ft_strchr.c\
			  ft_strrchr.c\
			  ft_strstr.c\
			  ft_strnstr.c\
			  ft_strcmp.c\
			  ft_strncmp.c\
			  ft_atoi.c\
			  ft_atol.c\
			  ft_isalpha.c\
			  ft_isalnum.c\
			  ft_isascii.c\
			  ft_isdigit.c\
			  ft_isprint.c\
			  ft_toupper.c\
			  ft_tolower.c\
			  ft_putchar.c\
			  ft_putstr.c\
			  ft_putendl.c\
			  ft_putnbr.c\
			  ft_putchar_fd.c\
			  ft_putstr_fd.c\
			  ft_putendl_fd.c\
			  ft_putnbr_fd.c\
			  ft_memalloc.c\
			  ft_memdel.c\
			  ft_strnew.c\
			  ft_strdel.c\
			  ft_strclr.c\
			  ft_striter.c\
			  ft_striteri.c\
			  ft_strmap.c\
			  ft_strmapi.c\
			  ft_strequ.c\
			  ft_strnequ.c\
			  ft_strsub.c\
			  ft_strjoin.c\
			  ft_strtrim.c\
			  ft_strsplit.c\
			  ft_itoa.c\
			  ft_power.c\
			  ft_putadresse.c\
			  ft_puttab.c\
			  get_next_line.c\
			  ft_nbrlen.c

OBJ_PATH    = obj
OBJ_NAME	= $(SRC_NAME:.c=.o)
INC_PATH	= .
HEADER		= $(INC_PATH)/libft.h

CC			= gcc

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
CFLAGS		= -Wall -Werror -Wextra

all : $(NAME)
	@echo "\033[48;5;22m\033[38;5;15m Libft Compiler \033[0m"

$(NAME) : $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(INC_PATH) $(CFLAGS) -c $< -o $@
	@ar rc $(NAME) $@
	@printf "\033[48;5;28m "

clean :
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	@rm -f $(NAME)

re : fclean all

nonor:
	@norminette *.c *.h