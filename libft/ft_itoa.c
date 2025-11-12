/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:39:19 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/08 07:58:40 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numbers(int c)
{
	int	count;

	count = 0;
	if (c <= 0)
		count = 1;
	while (c != 0)
	{
		c /= 10;
		count++;
	}
	return (count);
}

static char	*ft_print(char *result, int number, int len)
{
	result[len] = '\0';
	while (number != 0)
	{
		result[--len] = (number % 10) + '0';
		number /= 10;
	}
	return (result);
}

char	*ft_itoa(int c)
{
	size_t	len;
	char	*result;
	int		number;

	if (c == -2147483648)
		return (ft_strdup("-2147483648"));
	len = count_numbers(c);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (c == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	if (c < 0)
	{
		result[0] = '-';
		number = -c;
	}
	else
		number = c;
	ft_print(result, number, len);
	return (result);
}

/*static int	get_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*s_nb;

	len = get_size(n);
	nbr = n;
	s_nb = malloc((sizeof(char) * len) + 1);
	if (!s_nb)
		return (NULL);
	s_nb[len] = '\0';
	if (n < 0)
	{
		s_nb[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		s_nb[0] = '0';
	--len;
	while (nbr > 0)
	{
		s_nb[len] = (nbr % 10) + '0';
		nbr /= 10;
		--len;
	}
	return (s_nb);
}

#include <stdio.h>
#include "libft.h"

int main() {
    int num = -12345;
    char *str = ft_itoa(num);
    printf("Integer to string: %s\n", str);
    free(str);
    return 0;
}*/
