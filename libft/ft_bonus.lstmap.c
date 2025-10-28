/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:52 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:27:01 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_ele;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_ele = ft_lstnew(content);
		if (!new_ele)
		{
			ft_lstclear(&new_lst, del);
			del(content);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_ele);
		lst = lst->next;
	}
	return (new_lst);
}
/*
#include <stdio.h>
#include "libft.h"

void *to_upper(void *content) {
    char *str = strdup((char *)content);
    for (int i = 0; str[i]; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    return str;
}

void del(void *content) {
    free(content);
}

int main() {
    t_list *head = ft_lstnew("hello");
    t_list *second = ft_lstnew("world");
    ft_lstadd_back(&head, second);

    t_list *new_list = ft_lstmap(head, to_upper, del);

    t_list *temp = new_list;
    while (temp) {
        printf("Mapped content: %s\n", (char *)temp->content);
        temp = temp->next;
    }

    ft_lstclear(&new_list, del);
    ft_lstclear(&head, free);
    return 0;
}*/
