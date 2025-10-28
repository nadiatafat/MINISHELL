/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:19:31 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/18 14:17:37 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *str)
{
	int	has_digit;

	if (str == NULL || *str == '\0')
		return (0);
	has_digit = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			has_digit = 1;
		else
			return (0);
		str++;
	}
	return (has_digit);
}
