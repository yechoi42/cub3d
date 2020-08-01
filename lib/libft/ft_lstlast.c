/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:47:54 by yechoi            #+#    #+#             */
/*   Updated: 2020/04/03 22:07:19 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;
	int		count;

	count = ft_lstsize(lst);
	curr = lst;
	while (count > 1)
	{
		curr = curr->next;
		count--;
	}
	return (curr);
}
