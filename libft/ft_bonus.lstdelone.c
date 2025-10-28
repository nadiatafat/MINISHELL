/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:32:27 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:18:39 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void    del(void *content)
{
    free(content);
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>
#include "libft.h"

void del(void *content) {
    printf("Deleting: %s\n", (char *)content);
}

int main() {
    t_list *node = ft_lstnew("Hello");
    ft_lstdelone(node, del);
    return 0;
}*/
