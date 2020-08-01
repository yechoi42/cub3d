/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:10:20 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:09:42 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_tex_color(t_tex *tex, int type, t_pos *pos)
{
	if (pos->x >= 0 && pos->x < tex[type].width &&
			pos->y >= 0 && pos->y < tex[type].height)
	{
		return (*(tex[type].texture + ((int)tex[type].width *
						(int)pos->y + (int)pos->x)));
	}
	return (0x0);
}

void	render_a_stripe(t_game *game, t_config c, t_ray *ray, int rayid)
{
	int		i;
	int		color;
	t_pos	pos[3];
	double	dist_to_camera;
	double	wall_height;

	dist_to_camera = (c.width / 2) / tan(c.fov / 2);
	wall_height = c.tile * dist_to_camera / ray[rayid].distance;
	set_pos(&pos[0], c.width, c.height);
	set_pos(&pos[1], c.width / game->config.width * rayid,
		max(0, pos[0].y / 2 + c.eyelevel - wall_height / 2 - 1));
	pos[2].x = ray[rayid].washitvertical ?
	(int)fmod(ray[rayid].wallhit.y, c.tile) / c.tile
	* c.tex[ray[rayid].wallhitcontent].width :
	(int)fmod(ray[rayid].wallhit.x, c.tile) / c.tile
	* c.tex[ray[rayid].wallhitcontent].width;
	i = -1;
	while (++i < wall_height && ++pos[1].y < pos[0].y)
	{
		restrain_pos(&pos[1], &pos[0]);
		pos[2].y = (pos[1].y - (pos[0].y / 2 + c.eyelevel - wall_height / 2))
			/ wall_height * c.tex[ray[rayid].wallhitcontent].height;
		color = get_tex_color(c.tex, ray[rayid].wallhitcontent, &pos[2]);
		color ? game->img.data[to_coord(pos[1].x, pos[1].y, game)] = color : 0;
	}
}

void	render_ceiling(t_game *game)
{
	t_pos a1;
	t_pos a2;

	set_pos(&a1, 0, game->config.height / 2 + game->config.eyelevel);
	set_pos(&a2, game->config.width, game->config.height);
	draw_rectangle(game, a1, a2, game->config.ceiling_color);
}

void	render_floor(t_game *game)
{
	t_pos a1;
	t_pos a2;

	set_pos(&a1, 0, 0);
	set_pos(&a2, game->config.width,
			game->config.height / 2 + game->config.eyelevel);
	draw_rectangle(game, a1, a2, game->config.floor_color);
}
