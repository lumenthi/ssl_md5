/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 10:52:50 by lumenthi          #+#    #+#             */
/*   Updated: 2022/12/12 11:39:07 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void *new_ptr = malloc(size);

	if (new_ptr) {
		ft_bzero(new_ptr, size);
		if (ptr)
			ft_memmove(new_ptr, ptr, size);
	}

	if (ptr)
		free(ptr);

	return new_ptr;
}
