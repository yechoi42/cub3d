# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/11 18:18:57 by yechoi            #+#    #+#              #
#    Updated: 2020/08/01 16:13:12 by yechoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC_NAME = main.c \
		   init.c \
		   get_next_line.c \
		   keys.c\
		   pos.c \
		   parse1.c\
		   parse2.c \
		   move.c \
		   draw.c \
		   texture.c \
		   raycasting.c \
		   sprite.c \
		   mapcheck.c \
		   render.c \
		   utils.c \
		   utils2.c \
		   screenshot.c 
SRC_PATH = ./src
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAG) $(HEADER) -o $@ -c $<

BSRC_NAME = main_bonus.c \
		   init_bonus.c \
		   get_next_line_bonus.c \
		   keys_bonus.c\
		   pos_bonus.c \
		   parse1_bonus.c\
		   parse2_bonus.c \
		   move_bonus.c \
		   draw_bonus.c \
		   texture_bonus.c \
		   raycasting_bonus.c \
		   sprite_bonus.c \
		   mapcheck_bonus.c \
		   render_bonus.c \
		   utils_bonus.c \
		   utils2_bonus.c \
		   utils3_bonus.c \
		   screenshot_bonus.c 
BSRC_PATH = ./bonus
BSRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

BOBJ_NAME = $(BSRC_NAME:.c=.o)
BOBJ_PATH = ./bobj
BOBJ = $(addprefix $(BOBJ_PATH)/, $(BOBJ_NAME))
$(BOBJ_PATH)/%.o: $(BSRC_PATH)/%.c
	@mkdir $(BOBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAG) $(HEADER) -o $@ -c $<

SCREENSHOT = screenshot.bmp

HEADER	= -I./includes

CFLAG	= -Wall -Wextra -Werror 

LIBFT	= libft.a

LIBMLX	= libmlx.a

MLX	= -framework OpenGL -framework Appkit

LIBS	= -L./lib/libft -lft -L./lib/mlx -lmlx

RM	= rm -rf

all	: $(NAME)

$(NAME)	: $(OBJ) $(LIBFT) $(LIBMLX)
	gcc -o $(NAME) $(OBJ) $(HEADER) $(CFLAG) $(LIBS) $(MLX)

bonus	: $(BOBJ) $(LIBFT) $(LIBMLX)
	gcc -o $(NAME) $(BOBJ) $(HEADER) $(CFLAG) $(LIBS) $(MLX)

$(LIBFT):
	$(MAKE) -C lib/libft

$(LIBMLX):
	$(MAKE) -C lib/mlx

clean	:
	$(MAKE) -C lib/libft clean
	$(MAKE) -C lib/mlx clean
	rm -rf $(OBJ_PATH) $(BOBJ_PATH) $(SCREENSHOT)

fclean	: clean
	$(MAKE) -C lib/libft fclean
	rm -rf $(NAME)

re		: fclean all

.PHONY: all clean fclean re
