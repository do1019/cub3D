/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:39:17 by dogata            #+#    #+#             */
/*   Updated: 2021/01/23 11:14:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <limits.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_WINDOW_CLOSE	17
# define X_EVENT_FOCUS_IN		9

# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_ESC		65307
# define ARROW_KEY_L	65361
# define ARROW_KEY_R	65363
# define ARROW_KEY_UP	65362
# define ARROW_KEY_DOWN 65364

# define SUCCESS	1
# define ERROR		-1
# define MAX_ROW 	202
# define MAX_COL 	202
# define MAX_MAP 	200
# define MOVESPEED 	0.05
# define ROTSPEED 	0.05

# define TEX_NUM	5
# define TEX_WIDTH 	64
# define TEX_HEIGHT	64

# define FILE_HEADER_SIZE	14
# define INFO_HEADER_SIZE	40
# define HEADER_SIZE		54

typedef struct		s_bmp
{
	int				r_width;
	unsigned char	header_buf[HEADER_SIZE];
	unsigned char	*bmp_line;
	unsigned int	*tmp_line;
	unsigned int	file_size;
	unsigned int	offset_to_data;
	unsigned int	info_header_size;
	unsigned int	planes;
	unsigned int	color;
	unsigned long	compress;
	unsigned long	data_size;
	long			xppm;
	long			yppm;
	int				*rgb;
}					t_bmp;

typedef	struct		s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
}					t_rgb;

typedef struct		s_sprlst
{
	double			x;
	double			y;
	double			distance;
}					t_sprlst;

typedef struct		s_sprite
{
	double			*buffer;
	int				sprite_count;
	int				*sprite_order;
	double			*sprite_distance;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	long			draw_start_x;
	long			draw_start_y;
	long			draw_end_x;
	long			draw_end_y;
	int				stripe;
	int				spr_tex_x;
	int				spr_tex_y;
	int				color;
	int				**used;
	t_list			*head;
}					t_sprite;

typedef struct		s_texture
{
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				**texture;
	int				tex_num;
}					t_texture;

typedef struct		s_raycast
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				map_x;
	int				map_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				color;
}					t_raycast;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			old_dir_x;
	double			old_plane_x;
	int				p_start_pos_x;
	int				p_start_pos_y;
	char			p_start_dir;
}					t_player;

typedef struct		s_img
{
	void			*img;
	int				*addr;
	int				line_length;
	int				bpp;
	int				endian;
	int				img_width;
	int				img_height;
	t_rgb			*rgb;
}					t_img;

typedef struct		s_map
{
	int				map[MAX_ROW - 2][MAX_COL - 2];
	int				readmap[MAX_ROW][MAX_COL];
	int				copymap[MAX_ROW][MAX_COL];
	bool			map_initialized;
	bool			map_search_started;
	bool			map_end;
	int				start_location_count;
	int				max_row;
	int				max_col;
	int				map_line;
}					t_map;

typedef struct		s_conf
{
	int				x_render_size;
	int				y_render_size;
	char			*texture_path[5];
	int				floor_color[3];
	int				ceilling_color[3];
	bool			id_r_flag;
	bool			id_no_flag;
	bool			id_so_flag;
	bool			id_we_flag;
	bool			id_ea_flag;
	bool			id_s_flag;
	bool			id_f_flag;
	bool			id_c_flag;
	ssize_t			f_color;
	ssize_t			c_color;
	t_map			map;
}					t_conf;

typedef struct		s_game
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_player		pl;
	t_conf			conf;
	t_raycast		rc;
	t_texture		tex;
	t_sprite		spr;
	t_bmp			bmp;
	bool			key_flag;
	bool			save_flag;
}					t_game;

int					is_valid_command_line_argument
						(int argc, char **argv, t_game *game);
int					is_valid_configuration_file(char **argv, t_game *game);
int					is_valid_id_r(char *line, t_game *game);
int					is_valid_id_textures(char *line, t_game *game);
int					is_valid_id_colors(char *line, t_game *game);
int					is_valid_map_format(char *line, t_game *game);
int					is_valid_map(t_game *game);

int					is_player_location(char c);

void				set_player_info(t_game *game);
int					set_color_info(t_game *game);

void				window_init(t_game *game);
void				img_init(t_game *game);

void				game_struct_init(t_game *game);
void				bmp_struct_init(t_game *game);

int					putstr_error(char *s);
int					putstr_perror(char *s);
int					free_dp_rt(char ***tmp, int rt);
int					free_sp_rt(char **tmp, int rt);

void				texture_buffer_init(t_game *game);
int					load_image(t_game *game, int *texture, char *path);
int					load_texture(t_game *game);

int					deal_key(int key_code, t_game *game);
void				pressed_w_up(t_game *game);
void				pressed_s_down(t_game *game);
void				pressed_a(t_game *game);
void				pressed_d(t_game *game);

ssize_t				convert_rgb_to_int(int *target);

t_sprlst			*spr_lstnew(double x, double y);
void				sort_sprites(t_game *game);

void				output_bmp(t_game *game);

int					*dec_to_rgb(unsigned int num);
t_rgb				*create_rgb_array(int width, int height);
void				output_bmp_mem_allocation(t_game *game, int fd);
void				store_rgb_info_to_rgb_struct(t_game *game, int i, int j);
void				store_rgb_info_to_bmp_line(t_game *game, int i, int j);

void				information_display(t_game *game);

void				display_f_color(t_game *game);
void				display_c_color(t_game *game);

int					main_loop(t_game *game);

void				my_mlx_pixel_put(t_game *game, int x, int y, int color);
void				draw_floor_ceiling(t_game *game);
void				draw_wall_texture(t_game *game, int x);
void				draw_sprite(t_game *game);
int					redraw(t_game *game);
void				draw_sprite_put_pixel(t_game *game);

void				raycast_calculation(t_game *game);

void				calc_draw_wall(t_game *game);
void				calc_draw_texture(t_game *game);

void				update_current_sprite(t_game *game,
						t_list **current_lst, t_sprlst **current_spr);
void				calc_sprite_distance(t_game *game,
						t_list **current_lst, t_sprlst **current_spr);
void				calc_sprite_pos_size(t_game *game, t_sprlst **current_spr);
void				calc_sprite_draw_pixel_height_width(t_game *game);
void				calc_draw_sprite(t_game *game);

#endif
