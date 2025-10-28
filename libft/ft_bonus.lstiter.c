/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:34:10 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:22:00 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
#include "libft.h"

void print_node(void *content) {
    printf("Node content: %s\n", (char *)content);
}

int main() {
    t_list *head = ft_lstnew("First");
    t_list *second = ft_lstnew("Second");
    t_list *third = ft_lstnew("Third");
    ft_lstadd_back(&head, second);
    ft_lstadd_back(&head, third);
    ft_lstiter(head, print_node);
    ft_lstclear(&head, free);
    return 0;
}*/
