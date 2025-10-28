/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:31:49 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/24 15:06:52 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char c = '5';
    printf("Is '%c' a digit? %d\n", c, ft_isdigit(c));
    c = 'a';
    printf("Is '%c' a digit? %d\n", c, ft_isdigit(c));
    return 0;
}*/
