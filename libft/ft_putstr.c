/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 11:52:59 by lumenthi          #+#    #+#             */
/*   Updated: 2022/12/12 09:41:33 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr(const char *str)
{
	if (str == NULL)
		return;

	write(STDOUT_FILENO, str, ft_strlen(str));
}
