/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:27:01 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/24 15:12:43 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/*int	ft_toupper(int character)

{
	if (character >= 'a' && character <= 'z')
		return (character + ('A' - 'a'));
	return (character);
}

int main(void)
{
    int c = 'w';
    printf("%c", ft_toupper(c));
    return (0);
}*/
