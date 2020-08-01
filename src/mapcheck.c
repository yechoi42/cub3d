/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:07:39 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:09:46 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_space_around_position(t_game *game, int i, int j)
{
	if (i <= 0 || i >= game->config.rows || j <= 0 || j >= game->config.colums)
		return (0);
	else if (game->config.map[i][j + 1] == ' '
	|| game->config.map[i][j + 1] == '\0' || game->config.map[i][j - 1] == ' ')
		return (0);
	else if ((int)ft_strlen(game->config.map[i - 1]) <= j
	|| game->config.map[i - 1][j] == ' ' || game->config.map[i - 1][j] == '\0')
		return (0);
	else if ((int)ft_strlen(game->config.map[i + 1]) <= j
	|| game->config.map[i + 1][j] == ' ' || game->config.map[i + 1][j] == '\0')
		return (0);
	return (1);
}

double	find_angle(char c)
{
	if (c == 'N')
		return (M_PI / 2 * 3);
	else if (c == 'S')
		return (M_PI / 2);
	else if (c == 'E')
		return (0);
	else
		return (M_PI);
}

int		check_angle_pos(t_game *g, int i, int j)
{
	if (g->player.x || g->player.y)
		return (0);
	g->player.rotationangle = find_angle(g->config.map[i][j]);
	g->player.x = (j + .5) * g->config.tile;
	g->player.y = (i + .5) * g->config.tile;
	return (1);
}

int		check_map_validation(t_game *g, t_config c)
{
	static int	i = -1;
	int			j;

	while (g->config.map[++i])
	{
		j = -1;
		while (g->config.map[i][++j])
		{
			if (ft_strchr(NSEW, g->config.map[i][j]))
			{
				if (!check_angle_pos(g, i, j))
					return (0);
			}
			else if (c.map[i][j] == '0' || c.map[i][j] == '2')
			{
				if (!check_space_around_position(g, i, j))
					return (0);
			}
			else if (ft_strchr("1 ", g->config.map[i][j]))
				continue ;
			else
				return (0);
		}
	}
	return (1);
}

int		check_all_type(t_game *game)
{
	int i;
	int fd;

	fd = 0;
	if (!game->config.width || !game->config.height || !game->config.rows
			|| !game->config.colums || !game->config.tile)
		return (0);
	i = -1;
	while (++i < TEXTURES - 3)
		if (!game->config.tex[i].tex_path)
			return (0);
	if (!game->config.floor_color || !game->config.ceiling_color)
		return (0);
	return (1);
}
