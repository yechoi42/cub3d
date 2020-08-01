/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:08:58 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:09:43 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos		cast_horz_ray(t_game *game, t_config c, t_ray *r, double angle)
{
	t_pos	win;
	t_pos	intercept;
	t_pos	tocheck;
	t_pos	step;
	t_pos	next;

	intercept.y = floor(game->player.y / c.tile) * c.tile;
	intercept.y += r->isdown ? c.tile : 0;
	intercept.x = game->player.x + (intercept.y - game->player.y) / tan(angle);
	set_pos(&step, c.tile / tan(angle), c.tile * (r->isup ? -1 : 1));
	(r->isleft && step.x > 0) || (r->isright && step.x < 0) ? step.x *= -1 : 0;
	set_pos(&next, intercept.x, intercept.y);
	while (next.x > 0 && next.x < c.width && next.y > 0 && next.y < c.height)
	{
		set_pos(&tocheck, next.x, next.y + (r->isup ? -1 : 0));
		if (is_sprite(tocheck.x, tocheck.y, game) &&
				!r->sprite.horzhit.x && !r->sprite.horzhit.y)
			copy_pos(&r->sprite.horzhit, &tocheck);
		if (is_wall(tocheck.x, tocheck.y, game))
			return (next);
		set_pos(&next, next.x + step.x, next.y + step.y);
	}
	set_pos(&win, c.width, c.height);
	restrain_pos(&next, &win);
	return (next);
}

t_pos		cast_vert_ray(t_game *game, t_config c, t_ray *r, double angle)
{
	t_pos	win;
	t_pos	intercept;
	t_pos	tocheck;
	t_pos	step;
	t_pos	next;

	intercept.x = floor(game->player.x / c.tile) * c.tile;
	intercept.x += r->isright ? c.tile : 0;
	intercept.y = game->player.y + (intercept.x - game->player.x) * tan(angle);
	set_pos(&step, c.tile * (r->isleft ? -1 : 1), c.tile * tan(angle));
	step.y *= ((r->isup && step.y > 0) || (r->isdown && step.y < 0)) ? -1 : 1;
	set_pos(&next, intercept.x, intercept.y);
	while (next.x > 0 && next.x < c.width && next.y > 0 && next.y < c.height)
	{
		set_pos(&tocheck, next.x + (r->isleft ? -1 : 0), next.y);
		if (is_sprite(tocheck.x, tocheck.y, game) &&
				!r->sprite.verthit.x && !r->sprite.verthit.y)
			copy_pos(&r->sprite.verthit, &tocheck);
		if (is_wall(tocheck.x, tocheck.y, game))
			return (next);
		set_pos(&next, next.x + step.x, next.y + step.y);
	}
	set_pos(&win, c.width, c.height);
	restrain_pos(&next, &win);
	return (next);
}

static int	find_wall_hit_content(t_ray *r)
{
	if (r->isdown && !r->washitvertical)
		return (C_NO);
	else if (r->isup && !r->washitvertical)
		return (C_SO);
	else if (r->isleft && r->washitvertical)
		return (C_EA);
	else
		return (C_WE);
}

static void	check_ray_direction(t_ray *ray, double rayangle)
{
	ray->rayangle = rayangle;
	ray->isdown = rayangle > 0 && rayangle < M_PI;
	ray->isup = !ray->isdown;
	ray->isright = rayangle < (M_PI / 2) || rayangle > 1.5 * M_PI;
	ray->isleft = !ray->isright;
}

void		cast_a_ray(t_game *game, t_ray *ray, double rayangle)
{
	t_pos	horzhit;
	t_pos	verthit;
	double	horzdist;
	double	vertdist;

	rayangle = normalize_angle(rayangle);
	check_ray_direction(ray, rayangle);
	horzhit = cast_horz_ray(game, game->config, ray, rayangle);
	verthit = cast_vert_ray(game, game->config, ray, rayangle);
	horzdist = hypot(game->player.x - horzhit.x, game->player.y - horzhit.y);
	vertdist = hypot(game->player.x - verthit.x, game->player.y - verthit.y);
	if (vertdist < horzdist)
	{
		ray->distance = vertdist * cos(rayangle - game->player.rotationangle);
		ray->wallhit = verthit;
		ray->washitvertical = TRUE;
	}
	else
	{
		ray->distance = horzdist * cos(rayangle - game->player.rotationangle);
		ray->wallhit = horzhit;
		ray->washitvertical = FALSE;
	}
	ray->wallhitcontent = find_wall_hit_content(ray);
}
