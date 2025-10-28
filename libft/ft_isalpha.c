/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:13:22 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/24 15:03:04 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int dec)
{
	if ((dec >= 'a' && dec <= 'z') || (dec >= 'A' && dec <= 'Z'))
		return (1);
	return (0);
}

/*
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char c = 'A';
    printf("Is '%c' alphabetic? %d\n", c, ft_isalpha(c));
    c = '1';
    printf("Is '%c' alphabetic? %d\n", c, ft_isalpha(c));
    return 0;
}*/
