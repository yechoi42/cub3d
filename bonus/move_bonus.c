/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:41:24 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:14:22 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(double x, double y, t_game *game)
{
	int gridx;
	int gridy;

	if (x < 0 || x > game->config.width || y < 0 || y > game->config.height)
		return (1);
	gridx = (int)floor(x / game->config.tile);
	gridy = (int)floor(y / game->config.tile);
	if (gridx <= 0 || gridx >= game->config.colums
			|| gridy <= 0 || gridy >= game->config.rows)
		return (1);
	else if (game->config.map[gridy][gridx] == '1' ||
			game->config.map[gridy][gridx] == ' ' ||
			game->config.map[gridy][gridx] == '\0')
		return (1);
	return (0);
}

int		is_sprite(double x, double y, t_game *game)
{
	int gridx;
	int gridy;

	if (x < 0 || x > game->config.width || y < 0 || y > game->config.height)
		return (0);
	gridx = (int)floor(x / game->config.tile);
	gridy = (int)floor(y / game->config.tile);
	if (gridx <= 0 || gridx >= game->config.colums
			|| gridy <= 0 || gridy >= game->config.rows)
		return (0);
	if (game->config.map[gridy][gridx] == '2')
		return (SPRITE);
	else if (game->config.map[gridy][gridx] == '3')
		return (TUNA);
	return (0);
}

double	normalize_angle(double angle)
{
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

/*
** mv[0] move_angle mv[1] move_step
*/

void	move_player(t_game *g)
{
	float	mv[2];
	t_pos	new;
	double	newlevel;

	newlevel = g->config.eyelevel + g->player.eyelevel * g->config.updown_speed;
	if (newlevel < g->config.height / 4 && newlevel > -g->config.height / 4)
		g->config.eyelevel = newlevel;
	g->player.rotationangle += g->player.turndirection * g->player.turnspeed;
	mv[1] = g->player.walkdirection * g->player.walkspeed;
	if (g->player.walkdirection_lr)
	{
		mv[0] = normalize_angle(g->player.rotationangle
				- g->player.walkdirection_lr * M_PI / 2);
		set_pos(&new, g->player.x + cos(mv[0]) * mv[1],
				g->player.y + sin(mv[0]) * mv[1]);
	}
	else
		set_pos(&new, g->player.x + cos(g->player.rotationangle) * mv[1],
				g->player.y + sin(g->player.rotationangle) * mv[1]);
	if ((!is_wall(new.x, new.y, g) && !is_sprite(new.x, new.y, g))
			|| is_sprite(new.x, new.y, g) == 3)
	{
		g->player.x = new.x;
		g->player.y = new.y;
	}
}
