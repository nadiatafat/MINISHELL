/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:21:44 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/24 15:09:22 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
#include <stdio.h>
#include "libft.h"

int main() {
    char c = ' ';
    printf("Is '%c' printable? %d\n", c, ft_isprint(c));
    c = '\n';
    printf("Is '%c' printable? %d\n", c, ft_isprint(c));
    return 0;
}*/
