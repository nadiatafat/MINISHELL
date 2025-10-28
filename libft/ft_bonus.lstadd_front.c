/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:37:50 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:08:30 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
#include "libft.h"

int main() {
    t_list *head = ft_lstnew("Second");
    t_list *new = ft_lstnew("First");
    ft_lstadd_front(&head, new);
    printf("Head content: %s\n", (char *)head->content);
    free(new);
    free(head);
    return 0;
}*/
