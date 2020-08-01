/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:08:21 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/30 14:41:46 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int g_fd;
int g_ret;

static int	is_cub_file(char const *conf_path)
{
	int ret;
	int len;

	ret = 1;
	len = ft_strlen(conf_path);
	if (len >= 4)
		ret = ft_strncmp(conf_path + len - 4, ".cub", 4);
	return (ret == 0 ? 1 : 0);
}

static int	check_map_component(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("0123NSEW ", line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static int	check_type(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	else if (check_map_component(line))
		return (C_MAP);
	return (-1);
}

static int	is_blank_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int			parse_config(t_game *game, t_config *config, char const *conf_path)
{
	int				type;
	char			*line;

	if (!(is_cub_file(conf_path)))
		return (exit_error(game, EXIT_FAILURE, "ERROR\nnot cub file\n"));
	if ((g_fd = open(conf_path, O_RDONLY)) < 0)
		return (exit_error(game, EXIT_FAILURE, "ERROR\ncannot open file\n"));
	g_ret = 1;
	while ((g_ret = get_next_line(g_fd, &line)) > 0)
	{
		if ((type = check_type(line)) == -1)
			return (exit_error(game, EXIT_FAILURE, "ERROR\nwrong type"));
		if (is_blank_line(line) && !(config->map))
		{
			free(line);
			continue;
		}
		else if (is_blank_line(line) && config->map && g_ret)
			return (exit_error(game, EXIT_FAILURE, "ERROR\nblank line in map"));
		if (!parse_by_type(g_ret, config, type, line))
			return (0);
	}
	parse_by_type(g_ret, config, type, line);
	close(g_fd);
	return (1);
}
