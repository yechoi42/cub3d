/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:58:13 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 14:53:06 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_error(t_game *game, int code, char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	exit(code);
	free_machine(game);
	return (code);
}

void	cast_all_rays(t_game *game)
{
	t_ray		ray[game->config.width];
	int			id;
	double		rayangle;

	rayangle = game->player.rotationangle - (game->config.fov / 2);
	id = -1;
	while (++id < game->config.width)
	{
		init_sprite(&ray[id].sprite);
		cast_a_ray(game, &ray[id], rayangle);
		render_a_stripe(game, game->config, ray, id);
		render_a_sprite(game, game->config, &ray[id], id);
		rayangle += game->config.fov / game->config.width;
	}
}

int		main_loop(t_game *game)
{
	move_player(game);
	render_ceiling(game);
	render_floor(game);
	cast_all_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_game game;

	if (!(argc == 2 || (argc == 3 && !ft_strncmp(argv[2], "--save", 6))))
		return (exit_error(&game, EXIT_FAILURE, "ERROR\nargument error"));
	init_player(&game);
	init_config(&game);
	if (!parse_config(&game, &game.config, argv[1]))
		return (exit_error(&game, EXIT_FAILURE, "ERROR\nparsing map error"));
	if (!check_all_type(&game))
		return (exit_error(&game, EXIT_FAILURE, "ERROR\ntype error"));
	if (!check_map_validation(&game, game.config))
		return (exit_error(&game, EXIT_FAILURE, "ERROR\ninvalid map"));
	init_game(&game);
	load_texture(&game);
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
		return (screenshot(&game));
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_game, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
