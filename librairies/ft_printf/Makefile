
NAME		= libftprintf.a

SRC_PATH	= src/*
SRC_NAME	= int.c \
			  short.c \
			  short_short.c \
			  long_long.c \
			  long.c \
			  option_diouxx.c \
			  ft_atoi.c \
			  ft_power.c \
			  ft_strchr.c \
			  ft_strlen.c \
			  ft_strlenc.c \
			  ft_upower.c \
			  nbr_len_base.c \
			  unbr_len_base.c \
			  ft_champs.c \
			  option.c \
			  option2.c \
			  ft_put_double.c \
			  ft_putadress.c \
			  ft_putchar.c \
			  ft_putnbr_in_hexa.c \
			  ft_putnbr_in_octo.c \
			  ft_putnbr.c \
			  ft_putstr.c \
			  ft_putstrc.c \
			  ft_putnstr.c \
			  ft_putunbr.c \
			  ft_printf.c

OBJ_PATH    = ./obj

OBJ_NAME	= $(SRC_NAME:.c=.o)
INC_PATH	= include/
HEADER		= $(INC_PATH)ft_printf.h

CC			= gcc

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CFLAGS		= -Wall -Werror -Wextra

all : $(NAME)
	@echo "\033[48;5;22m\033[38;5;15m Libftprintf Compiler \033[0m"

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

nonor :
	@norminette src/*/*.c include/*.h