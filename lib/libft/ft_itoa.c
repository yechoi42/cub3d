/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:53:15 by yechoi            #+#    #+#             */
/*   Updated: 2020/04/06 16:18:17 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		find_jaritsu(int n)
{
	int				jaritsu;
	unsigned int	n2;

	jaritsu = 1;
	n2 = (n < 0 ? (unsigned int)(n * (-1)) : (unsigned int)n);
	while (n2 >= 10)
	{
		n2 = n2 / 10;
		jaritsu++;
	}
	return (jaritsu);
}

char	*ft_itoa(int n)
{
	int				jaritsu;
	char			*buff;
	unsigned int	n2;

	jaritsu = (n < 0 ? find_jaritsu(n) + 1 : find_jaritsu(n));
	if (!(buff = (char *)malloc(sizeof(char) * (jaritsu + 1))))
		return (NULL);
	buff[jaritsu] = '\0';
	n2 = (n < 0 ? (unsigned int)n * (-1) : (unsigned int)n);
	while (jaritsu > 0)
	{
		buff[jaritsu - 1] = (n2 % 10) + '0';
		n2 = n2 / 10;
		jaritsu--;
	}
	if (n < 0)
		buff[0] = '-';
	return (buff);
}
