/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:54:06 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:09:33 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
/*
#include <stdio.h>
#include "libft.h"

int main() {
    t_list *head = ft_lstnew("First");
    t_list *new = ft_lstnew("Second");
    ft_lstadd_back(&head, new);
    printf("Second node content: %s\n", (char *)head->next->content);
    free(head->next);
    free(head);
    return 0;
}*/
