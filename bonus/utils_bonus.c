/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:03:35 by yechoi            #+#    #+#             */
/*   Updated: 2020/08/01 19:08:38 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define M 0.3
#define BAR 0.5

void	render_a_ray(t_game *game, t_ray ray)
{
	t_pos	player;
	t_pos	wallhit;

	set_pos(&player, game->player.x * M, game->player.y * M);
	set_pos(&wallhit, ray.wallhit.x * M, ray.wallhit.y * M);
	draw_line(game, player, wallhit, 0xffc0cb);
}

void	render_map(t_game *g, t_config c)
{
	t_index		i;
	t_pos		a[2];
	int			tile_color;

	i.y = -1;
	while (++i.y < g->config.rows)
	{
		i.x = -1;
		while (++i.x < g->config.colums && c.map[i.y][i.x] != '\0')
		{
			set_pos(&a[0], c.tile * i.x * M, c.tile * i.y * M);
			set_pos(&a[1], c.tile * (i.x + 1) * M, c.tile * (i.y + 1) * M + 1);
			if (is_sprite(i.x * c.tile, i.y * c.tile, g) ||
				!is_wall(i.x * c.tile, i.y * c.tile, g))
			{
				if (is_sprite(i.x * c.tile, i.y * c.tile, g) == 2)
					tile_color = 0x8977ad;
				else if (is_sprite(i.x * c.tile, i.y * c.tile, g) == 3)
					tile_color = 0xf6b65a;
				else
					tile_color = 0xd3d3d3;
				draw_rectangle(g, a[0], a[1], tile_color);
			}
		}
	}
}

void	render_player(t_game *game)
{
	t_pos	player;
	t_pos	coner;
	double	x;
	double	y;

	x = game->player.x;
	y = game->player.y;
	set_pos(&player, x * M, y * M);
	set_pos(&coner, x * M + 2, y * M + 2);
	draw_rectangle(game, player, coner, 0x000000);
}

void	render_lifebar(t_game *game)
{
	int		i;
	int		j;
	int		newx;
	int		newy;
	t_tex	lifebar;

	lifebar = game->config.tex[C_LB];
	i = -1;
	while (++i < lifebar.height)
	{
		j = -1;
		while (++j < lifebar.width)
		{
			newx = game->config.width - lifebar.width * BAR - 10 + j * BAR;
			newy = 10 + i * BAR;
			game->img.data[to_coord(newx, newy, game)] =
				lifebar.texture[(int)(i * lifebar.width + j)];
		}
	}
}
