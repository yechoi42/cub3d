/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:06:33 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/16 13:27:54 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		to_coord(int x, int y, t_game *game)
{
	int ret;

	ret = (int)floor(y) * game->config.width + (int)floor(x);
	return (ret);
}

void	draw_line(t_game *game, t_pos a1, t_pos a2, int color)
{
	double	deltax;
	double	deltay;
	double	step;
	t_pos	win;

	set_pos(&win, game->config.width, game->config.height);
	restrain_pos(&a1, &win);
	restrain_pos(&a2, &win);
	deltax = a2.x - a1.x;
	deltay = a2.y - a1.y;
	step = (fabs(deltax) > fabs(deltay)) ? fabs(deltax) : fabs(deltay);
	deltax /= step;
	deltay /= step;
	while (fabs(a2.x - a1.x) > 0.5 || fabs(a2.y - a1.y) > 0.5)
	{
		game->img.data[to_coord(a1.x, a1.y, game)] = color;
		a1.x += deltax;
		a1.y += deltay;
	}
}

void	draw_rectangle(t_game *game, t_pos p1, t_pos p2, int color)
{
	int		i;
	t_pos	win;
	t_pos	a1;
	t_pos	a2;

	set_pos(&win, game->config.width, game->config.height);
	restrain_pos(&p1, &win);
	restrain_pos(&p2, &win);
	i = p1.x;
	while (i < p2.x)
	{
		set_pos(&a1, i, p1.y);
		set_pos(&a2, i, p2.y);
		draw_line(game, a1, a2, color);
		i++;
	}
}
