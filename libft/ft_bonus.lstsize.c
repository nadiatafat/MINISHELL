/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:59:49 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:12:08 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
/*
#include <stdio.h>
#include "libft.h"

int main() {
    t_list *head = ft_lstnew("First");
    t_list *second = ft_lstnew("Second");
    t_list *third = ft_lstnew("Third");
    ft_lstadd_back(&head, second);
    ft_lstadd_back(&head, third);
    printf("List size: %d\n", ft_lstsize(head));
    free(third);
    free(second);
    free(head);
    return 0;
}*/
