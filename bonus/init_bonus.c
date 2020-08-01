/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:18:55 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:09:48 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.width = 0;
	game->player.height = 0;
	game->player.turndirection = 0;
	game->player.walkdirection = 0;
	game->player.walkdirection_lr = 0;
	game->player.rotationangle = M_PI / 2;
	game->player.walkspeed = 5;
	game->player.turnspeed = 3 * (M_PI / 180);
	game->player.rotationspeed = 0;
	game->player.eyelevel = 0;
}

void	init_config(t_game *game)
{
	int i;

	game->config.width = 0;
	game->config.height = 0;
	game->config.rows = 0;
	game->config.colums = 0;
	game->config.tile = 0;
	i = 0;
	while (i < TEXTURES)
		game->config.tex[i++].tex_path = NULL;
	game->config.floor_color = 0;
	game->config.ceiling_color = 0;
	game->config.map = NULL;
	game->config.rotation_speed = .11;
	game->config.move_speed = .11;
	game->config.updown_speed = 30;
	game->config.eyelevel = 0;
	game->config.fov = 80 * M_PI / 180;
	game->config.tuna = 0;
	game->config.t_num = 0;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx,
			game->config.width, game->config.height, "cub3d");
	game->img.img = mlx_new_image(game->mlx,
			game->config.width, game->config.height);
	game->img.data = (int *)mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.size_l, &game->img.endian);
}
