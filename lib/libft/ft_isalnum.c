/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:05:10 by yechoi            #+#    #+#             */
/*   Updated: 2020/04/03 22:40:06 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	else if (c >= 65 && c <= 90)
		return (c);
	else if (c >= 97 && c <= 122)
		return (c);
	return (0);
}
