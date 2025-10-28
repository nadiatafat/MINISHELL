/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:39:42 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:06:10 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(struct s_list));
	if (!new_lst)
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	return (new_lst);
}
/*
#include <stdio.h>
#include "libft.h"

int main() {
    t_list *node = ft_lstnew("Hello");
    if (node) {
        printf("Node content: %s\n", (char *)node->content);
        free(node);
    }
    return 0;
}*/
