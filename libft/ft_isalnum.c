/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:20:03 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:34:52 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include "libft.h"

int main() {
    char c = '9';
    printf("Is '%c' alphanumeric? %d\n", c, ft_isalnum(c));
    c = '!';
    printf("Is '%c' alphanumeric? %d\n", c, ft_isalnum(c));
    return 0;
}*/
