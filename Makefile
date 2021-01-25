# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 15:50:07 by dogata            #+#    #+#              #
#    Updated: 2020/12/25 08:52:43 by dogata           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
OFLAGS := -lXext -lX11 -lm -lbsd
LIBS := ar rcs
NAME := cub3D
NAME_MINILIBX := libmlx.a
NAME_LIBFT := libft.a
NAME_GNL := get_next_line.a
MINILIBX_DIR := minilibx-linux/
LIBFT_DIR := libft/
GNL_DIR := get_next_line/

SRCS := main.c \
		utils.c \
		init_mlx.c \
		init_struct.c \
		is_valid_command_line_argument.c \
		is_valid_configuration_file.c \
		is_valid_resolution.c \
		is_valid_textures.c \
		is_valid_colors.c \
		is_valid_map_format.c \
		is_valid_map.c \
		information_display.c \
		information_display_utils.c \
		set_info.c \
		convert_rgb.c \
		key_move_player.c \
		key_move_player_utils.c \
		output_bmp.c \
		output_bmp_utils.c \
		load_texture.c \
		sort_sprite.c \
		raycast_calc.c \
		raycast_calc_draw_wall_texture.c \
		raycast_calc_draw_sprite.c \
		raycast_draw.c \
		raycast_draw_utils.c \

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	make -C $(GNL_DIR)
	make -C $(MINILIBX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MINILIBX_DIR)$(NAME_MINILIBX) $(LIBFT_DIR)$(NAME_LIBFT) $(GNL_DIR)$(NAME_GNL) $(OFLAGS)

debug: $(NAME)
	@make bonus -C $(LIBFT_DIR)
	make -C $(GNL_DIR)
	make -C $(MINILIBX_DIR)
	$(CC) $(CFLAGS) -g  -fsanitize=address -o $(NAME) $(OBJS) $(MINILIBX_DIR)$(NAME_MINILIBX) $(LIBFT_DIR)$(NAME_LIBFT) $(GNL_DIR)$(NAME_GNL) $(OFLAGS)

clean:
	@rm -f $(OBJS) $(LIBFT_DIR)*.o $(GNL_DIR)*.o $(MINILIBX_DIR)*.o

fclean: clean
	@rm -f $(NAME) $(LIBFT_DIR)$(NAME_LIBFT) $(GNL_DIR)$(NAME_GNL) $(MINILIBX_DIR)$(NAME_MINILIBX)

re: fclean all

.PHONY: all bonus clean fclean re