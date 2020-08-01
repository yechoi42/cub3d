/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:06:48 by yechoi            #+#    #+#             */
/*   Updated: 2020/07/16 13:28:19 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*stack_buff_join(char *stack, char *buff)
{
	char	*temp;

	temp = ft_strjoin(stack, buff);
	free(stack);
	free(buff);
	return (temp);
}

static char	*update_line(char *stack, int ret)
{
	char	*line;
	int		pos;

	line = 0;
	pos = 0;
	if (ret == 0)
		line = ft_strdup(stack);
	else if (ret > 0)
	{
		while (stack[pos] != '\n')
			pos++;
		line = ft_substr(stack, 0, pos);
	}
	return (line);
}

static char	*update_stack(char *stack, int ret)
{
	int		pos;
	char	*temp;

	temp = 0;
	pos = 0;
	if (ret > 0)
	{
		while (stack[pos] != '\n')
			pos++;
		temp = ft_strdup(stack + pos + 1);
	}
	free(stack);
	stack = NULL;
	return (temp);
}

int			get_next_line(int fd, char **line)
{
	static char	*stack[1024] = {0, };
	int			ret;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	ret = 1;
	if (stack[fd] == 0)
		stack[fd] = ft_strdup("");
	while (ft_strchr(stack[fd], '\n') == 0 && ret > 0)
	{
		if (!(buff = ft_calloc(1, BUFFER_SIZE + 1)) ||
				(ret = read(fd, buff, BUFFER_SIZE)) < 0)
			return (-1);
		stack[fd] = stack_buff_join(stack[fd], buff);
	}
	*line = update_line(stack[fd], ret);
	stack[fd] = update_stack(stack[fd], ret);
	return (ret > 0 ? 1 : ret);
}
