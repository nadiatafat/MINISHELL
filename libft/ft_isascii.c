/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:21:21 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/24 15:09:51 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
int	ft_isascii(int character)
{
	if (character >= 0 && character <= 127)
		return (1);
	return (0);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char c = 127;
    printf("Is '%c' ASCII? %d\n", c, ft_isascii(c));
    c = -1;
    printf("Is '%c' ASCII? %d\n", c, ft_isascii(c));
    return 0;
}*/
