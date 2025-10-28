/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:10:47 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:16:03 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
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
    t_list *last = ft_lstlast(head);
    printf("Last node content: %s\n", (char *)last->content);
    free(third);
    free(second);
    free(head);
    return 0;
}*/
