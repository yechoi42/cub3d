/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 15:03:11 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:14:11 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_music(char *str)
{
	int	len;

	if ((len = ft_strlen(str)) >= 11 &&
			!ft_strncmp(str + len - 11, "pengsoo.cub", 11))
		system("afplay -v 0.30  music/pengsoo.mp3 &");
	else
		system("afplay -v 0.30 music/joy.mp3 &");
}

void	show_info(t_game *game)
{
	char	*msg;
	char	*tmp;
	char	*num;

	num = ft_itoa(game->player.walkspeed);
	msg = ft_strjoin("MOVE SPEED: ", num);
	mlx_string_put(game->mlx, game->win,
			game->config.width - 150, game->config.height - 30, 0xffffff, msg);
	free(msg);
	free(num);
	num = ft_itoa(game->config.tuna);
	tmp = ft_strjoin("I ate ", num);
	msg = ft_strjoin(tmp, " can(s) of tuna!");
	mlx_string_put(game->mlx, game->win,
			20, game->config.height - 30, 0xffffff, msg);
	free(num);
	free(msg);
	free(tmp);
}

void	print_config(t_game *game)
{
	int i;

	i = 0;
	printf("resolution %d %d\n", game->config.width, game->config.height);
	printf("colums, rows and tile %d %d %f\n",
			game->config.colums, game->config.rows, game->config.tile);
	while (i < TEXTURES)
		printf("%s\n", game->config.tex[i++].tex_path);
	printf("floor and ceiling color %d %d\n",
			game->config.floor_color, game->config.ceiling_color);
	i = -1;
	while (game->config.map[++i])
		printf("%s\n", game->config.map[i]);
	printf("starting position %f %f\n", game->player.x, game->player.y);
	printf("number of tunas %d\n", game->config.t_num);
}

char	*update_temp(char *temp, char *line)
{
	char *temp2;
	char *temp3;

	temp2 = ft_strjoin(line, "\n");
	temp3 = ft_strjoin(temp, temp2);
	if (*temp && temp)
	{
		free(temp);
		temp = NULL;
	}
	free(temp2);
	return (temp3);
}
