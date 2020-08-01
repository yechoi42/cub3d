/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:51:41 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:18:39 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_sprite *sprite)
{
	set_pos(&sprite->verthit, 0, 0);
	set_pos(&sprite->horzhit, 0, 0);
	set_pos(&sprite->hit, 0, 0);
	set_pos(&sprite->mappos, 0, 0);
	sprite->min_angle = 0;
	sprite->max_angle = 0;
	sprite->distance = 0;
	sprite->height = 0;
	sprite->tex_x = 0;
}

void	find_sprite_hit(t_game *game, t_ray *ray, t_sprite *sprite)
{
	double		horz_hit_dist;
	double		vert_hit_dist;

	horz_hit_dist = 0;
	vert_hit_dist = 0;
	if (ray->sprite.horzhit.x && ray->sprite.horzhit.y)
		horz_hit_dist = hypot(game->player.x - ray->sprite.horzhit.x,
				game->player.y - ray->sprite.horzhit.y);
	if (ray->sprite.verthit.x && ray->sprite.verthit.y)
		vert_hit_dist = hypot(game->player.x - ray->sprite.verthit.x,
				game->player.y - ray->sprite.verthit.y);
	if (((horz_hit_dist && horz_hit_dist < vert_hit_dist) ||
				(horz_hit_dist && !vert_hit_dist)))
		copy_pos(&sprite->hit, &ray->sprite.horzhit);
	else if (((vert_hit_dist && vert_hit_dist < horz_hit_dist) ||
				(vert_hit_dist && !horz_hit_dist)))
		copy_pos(&sprite->hit, &ray->sprite.verthit);
}

void	check_sprite_config(t_game *game, t_sprite *s, double angle)
{
	double		sprite_angle;

	if (s->hit.x && s->hit.y)
	{
		set_pos(&s->mappos, (int)floor(s->hit.x / game->config.tile),
				(int)floor(s->hit.y / game->config.tile));
		set_pos(&s->mapcenter, (s->mappos.x + 0.5) * game->config.tile,
				(s->mappos.y + 0.5) * game->config.tile);
		s->distance = hypot(game->player.x - s->mapcenter.x,
				game->player.y - s->mapcenter.y);
		sprite_angle = atan2(s->mapcenter.y - game->player.y,
				s->mapcenter.x - game->player.x);
		sprite_angle = normalize_angle(sprite_angle);
		s->min_angle = sprite_angle - atan2(game->config.tile / 2, s->distance);
		s->max_angle = sprite_angle + atan2(game->config.tile / 2, s->distance);
		angle = normalize_angle(angle);
		s->min_angle = normalize_angle(s->min_angle);
		s->max_angle = normalize_angle(s->max_angle);
		(s->max_angle < s->min_angle) ? s->max_angle += 2 * M_PI : 0;
		(angle < s->min_angle) ? angle += 2 * M_PI : 0;
		s->tex_x = (angle - s->min_angle) /
		(s->max_angle - s->min_angle) * game->config.tex[C_S].width - 0.0001;
	}
}

void	render_a_sprite(t_game *game, t_config c, t_ray *r, int rayid)
{
	int			i;
	t_pos		pos[3];
	int			color;
	double		dist_to_camera;

	find_sprite_hit(game, r, &r->sprite);
	check_sprite_config(game, &r->sprite, r->rayangle);
	if (!r->sprite.tex_x || r->distance < r->sprite.distance)
		return ;
	dist_to_camera = (c.width / 2) / tan(c.fov / 2);
	r->sprite.height = c.tile * dist_to_camera / r->sprite.distance;
	set_pos(&pos[0], c.width, c.height);
	set_pos(&pos[1], c.width / game->config.width * rayid,
		max(0, c.height / 2 + c.eyelevel - r->sprite.height / 2 - 1));
	pos[2].x = r->sprite.tex_x;
	i = -1;
	while (++i < r->sprite.height && ++pos[1].y < pos[0].y)
	{
		restrain_pos(&pos[1], &pos[0]);
		pos[2].y = (pos[1].y - (pos[0].y / 2 + c.eyelevel -
			r->sprite.height / 2)) / r->sprite.height * c.tex[C_S].height;
		color = get_tex_color(game->config.tex, C_S, &pos[2]);
		color ? game->img.data[to_coord(pos[1].x, pos[1].y, game)] = color : 0;
	}
}
