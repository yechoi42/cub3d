/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:40:36 by yechoi            #+#    #+#             */
/*   Updated: 2020/08/01 16:10:23 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define FALSE					0
# define TRUE					1
# define BUFFER_SIZE			16

# define KEY_1					18
# define KEY_2					19
# define KEY_3					20
# define KEY_4					21
# define KEY_Q					12
# define KEY_W					13
# define KEY_E					14
# define KEY_R					15
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_I					34
# define KEY_O					31
# define KEY_P					35
# define KEY_J					38
# define KEY_K					40
# define KEY_L					37
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_UP 				126
# define KEY_DOWN				125
# define KEY_MINUS				27
# define KEY_PLUS				24

# define KEY_TAB				48
# define KEY_MAJ				257
# define KEY_ESC				53

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_GAME_CLEAR		7
# define X_EVENT_KEY_EXIT		17

# define NSEW					"NSEW"
# define MOVESPEED				2

# define SPRITE					2
# define TUNA					3

# define TEXTURES				8
# define TEX_NORTH				0
# define TEX_SOUTH				1
# define TEX_WEST				2
# define TEX_EAST				3
# define TEX_SPRITE				4
# define TEX_TUNA				5
# define TEX_LB					6
# define TEX_GC					7

# define C_R					6
# define C_NO					0
# define C_SO					1
# define C_WE					2
# define C_EA					3
# define C_S					4
# define C_TUNA					5
# define C_LB					6
# define C_GC					7
# define C_F 					8
# define C_C					9
# define C_MAP					10

typedef struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct	s_index
{
	int			x;
	int			y;
}				t_index;

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_sprite
{
	int			content;
	t_pos		verthit;
	t_pos		horzhit;
	t_pos		hit;
	t_pos		mappos;
	t_pos		mapcenter;
	double		angle;
	double		min_angle;
	double		max_angle;
	double		distance;
	double		height;
	int			tex_x;
}				t_sprite;

typedef struct	s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			turndirection;
	int			walkdirection;
	int			walkdirection_lr;
	float		rotationangle;
	float		walkspeed;
	float		turnspeed;
	double		rotationspeed;
	double		eyelevel;
}				t_player;

typedef struct	s_ray
{
	double		rayangle;
	double		distance;
	t_pos		wallhit;
	t_sprite	sprite;
	int			washitvertical;
	int			isup;
	int			isdown;
	int			isleft;
	int			isright;
	int			wallhitcontent;
}				t_ray;

typedef struct	s_tex
{
	char		*tex_path;
	int			*texture;
	double		width;
	double		height;
}				t_tex;

typedef struct	s_config
{
	int			width;
	int			height;
	int			rows;
	int			colums;
	double		tile;
	t_tex		tex[TEXTURES];
	int			floor_color;
	int			ceiling_color;
	char		**map;
	double		rotation_speed;
	double		updown_speed;
	double		move_speed;
	double		eyelevel;
	double		fov;
	int			tuna;
	int			t_num;
}				t_config;

typedef struct	s_game
{
	t_config	config;
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
}				t_game;

/*
** main.c
*/

int				exit_error(t_game *game, int code, char const *str);
void			cast_all_rays(t_game *game);

/*
** get_next_line.c
*/

int				get_next_line(int fd, char **line);

/*
** draw.c
*/

int				to_coord(int x, int y, t_game *game);
void			draw_line(t_game *game, t_pos a1, t_pos a2, int color);
void			draw_rectangle(t_game *game, t_pos p1, t_pos p2, int color);

/*
** texture.c
*/

void			load_texture(t_game *game);

/*
** screenshot.c
*/

int				screenshot(t_game *game);

/*
** init.c
*/

void			init_player(t_game *game);
void			init_config(t_game *game);
void			init_game(t_game *game);

/*
** keys.c
*/

int				key_press(int key_code, t_game *game);
int				key_release(int key_code, t_game *game);
int				exit_game(void *parameter);

/*
** pos.c
*/

void			restrain_pos(t_pos *pos, t_pos *size);
void			set_pos(t_pos *pos, double x, double y);
void			copy_pos(t_pos *pos, t_pos *org);

/*
** parse1.c parse2.c
*/

int				parse_config\
					(t_game *game, t_config *config, char const *conf_path);
int				parse_by_type(int ret, t_config *config, int type, char *line);

/*
** move.c
*/

int				is_wall(double x, double y, t_game *game);
int				is_sprite(double x, double y, t_game *game);
double			normalize_angle(double angle);
void			move_player(t_game *game);

/*
** sprite.c
*/

void			init_sprite(t_sprite *sprite);
void			find_sprite_hit(t_game *game, t_ray *ray, t_sprite *sprite);
void			check_sprite_config\
					(t_game *game, t_sprite *sprite, double angle);
void			render_a_sprite(t_game *game, t_config c, t_ray *r, int rayid);

/*
** raycasting.c
*/

t_pos			cast_horz_ray(t_game *game, t_config c, t_ray *r, double angle);
t_pos			cast_vert_ray(t_game *game, t_config c, t_ray *r, double angle);
void			cast_a_ray(t_game *game, t_ray *ray, double rayangle);

/*
** render.c
*/

int				get_tex_color(t_tex *tex, int type, t_pos *pos);
void			render_a_stripe\
					(t_game *game, t_config config, t_ray *ray, int rayid);
void			render_ceiling(t_game *game);
void			render_floor(t_game *game);

/*
** mapcheck.c
*/

int				check_space_around_position(t_game *game, int i, int j);
double			find_angle(char c);
int				check_map_validation(t_game *g, t_config c);
int				check_all_type(t_game *game);

/*
** utils.c
*/

void			render_a_ray(t_game *game, t_ray ray);
void			render_map(t_game *game, t_config config);
void			render_player(t_game *game);
void			render_lifebar(t_game *game);
void			free_machine(t_game *game);

/*
** utils2.c
*/

double			max(double a, double b);
void			play_music(char *str);
void			show_info(t_game *game);
void			print_config(t_game *game);

/*
** utils3.c
*/
double			max(double a, double b);
int				is_upper(int x);
int				is_space(int x);
int				free_line(char *line, int ret);
char			*update_temp(char *temp, char *line);

#endif
