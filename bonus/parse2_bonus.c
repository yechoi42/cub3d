/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:08:36 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 15:14:17 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_resolution(t_config *config, char *line)
{
	int		i;
	int		width;
	int		height;

	i = 0;
	width = 0;
	height = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		width = width * 10 + line[i++] - 48;
	while (is_space(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		height = height * 10 + line[i++] - 48;
	config->width = width;
	config->height = height;
	return (1);
}

static char	*parse_path(char *line)
{
	int		i;
	char	*buff;

	i = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	buff = ft_strdup(line + i);
	return (buff);
}

static int	parse_color(char *line)
{
	int	i;
	int	j;
	int	color;
	int	colors[3];

	i = 0;
	j = 0;
	while (j < 3)
		colors[j++] = 0;
	while (is_upper(line[i]))
		i++;
	if (is_space(line[i]))
		i++;
	j = -1;
	while (line[i] && ++j < 3)
	{
		while (line[i] && ft_isdigit(line[i]))
			colors[j] = colors[j] * 10 + line[i++] - 48;
		if ((!ft_strchr(",", line[i]) && line[i] != '\0') || colors[j] > 255)
			return (-1);
		ft_strchr(",", line[i]) ? i++ : 0;
	}
	color = colors[0] * 256 * 256 + colors[1] * 256 + colors[2];
	return (color);
}

static int	parse_map(t_config *config, char *temp)
{
	int		i;
	int		j;

	if (!(config->map = ft_split(temp, '\n')))
		return (0);
	i = -1;
	j = 0;
	while (config->map[++i])
		j = j < (int)ft_strlen(config->map[i])
			? (int)ft_strlen(config->map[i]) : j;
	config->rows = i;
	config->colums = j;
	config->tile = config->width / config->colums;
	return (1);
}

int			parse_by_type(int ret, t_config *c, int tp, char *line)
{
	static char *temp = "";

	if (tp == C_R)
	{
		if (!parse_resolution(c, line))
			return (free_line(line, 0));
	}
	else if (tp >= C_NO && tp <= C_S)
	{
		if (c->tex[tp].tex_path || !(c->tex[tp].tex_path = parse_path(line)))
			return (free_line(line, 0));
	}
	else if (tp == C_F || tp == C_C)
	{
		if ((tp == C_F && (c->floor_color = parse_color(line)) == -1) ||
		(tp == C_C && (c->ceiling_color = parse_color(line)) == -1))
			return (free_line(line, 0));
	}
	else
	{
		temp = update_temp(temp, line);
		if (ret == 0 && !parse_map(c, temp))
			return (free_line(line, 0));
	}
	return (free_line(line, 1));
}
