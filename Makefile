# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/14 16:56:52 by matheme      #+#   ##    ##    #+#        #
#    Updated: 2019/04/30 15:52:26 by matheme     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

# nom de l'executable
NAME1 = ft_ls

# les routes
SRC_PATH	= src
OBJ_PATH	= obj
INC_PATH	= includes
LIB_PATH	= librairies

# nom des fichier code source (*.c)
NAME_SRC_LS	=	colonne_tool.c	\
				colonne.c		\
				deci_to_octo.c	\
				error.c			\
				ft_ls.c			\
				inspect.c		\
				lst_file.c		\
				lst_max.c		\
				option_l.c		\
				option_l2.c		\
				option.c		\
				sort.c			\
				tool.c

#nom des ficher objects (*.o)
NAME_OBJ_LS = $(NAME_SRC_LS:.c=.o)

#les sources
SRC_LS		= $(addprefix $(SRC_PATH)/,$(NAME_SRC_LS))
HEADER_LS	= $(INC_PATH)/ft_ls.h

# les objects
OBJ_LS		= $(addprefix $(OBJ_PATH)/,$(NAME_OBJ_LS))

#compilateur + flags
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

#librairies
LIBFT				= $(LIB_PATH)/libft
LIBFT.A				= $(LIBFT)/libft.a
FT_PRINTF			= $(LIB_PATH)/ft_printf
FT_PRINTF_INCLUDE	= $(FT_PRINTF)/include
FT_PRINTF.A			= $(FT_PRINTF)/libftprintf.a

all : libft ft_printf $(NAME1)
	@echo "\033[48;5;22m\033[38;5;15m ft_ls Compiler \033[0m"

$(NAME1) : $(OBJ_LS) $(LIBFT.A) $(FT_PRINTF.A)
	@$(CC) -I $(LIBFT) -L $(LIBFT) -I $(FT_PRINTF) -L $(FT_PRINTF_INCLUDE)/ $^ -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER_LS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@printf "\033[48;5;28m "
	@$(CC) -I $(LIBFT) -I $(INC_PATH) -c $< -o $@

libft :
	@make -C $(LIBFT)

ft_printf :
	@make -C $(FT_PRINTF)

clean :
	@rm -f $(OBJ_LS)
	@make -C $(LIBFT) clean
	@make -C $(FT_PRINTF) clean
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[48;5;1m\033[38;5;15m   binaire supprimer  \033[0m"

fclean: clean
	@make -C $(LIBFT) fclean
	@make -C $(FT_PRINTF) fclean
	@rm -f $(NAME1)
	@echo "\033[48;5;208m\033[38;5;15m tout a été supprimer \033[0m"

re: fclean all

nonor :
	@norminette src/*.c includes/*.h

supernonor: nonor
	@make -C $(LIBFT) nonor
	@make -C $(FT_PRINTF) nonor
