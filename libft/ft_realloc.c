/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:29:26 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/19 16:44:42 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size, int free_flag)
{
	void	*new_ptr;
	size_t	copy_size;

	// Si new_size == 0 : libération et retour NULL
	if (new_size == 0)
	{
		if (free_flag && ptr)
			free(ptr);
		return NULL;
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		// Ne surtout pas free ptr ici !
		// realloc doit laisser l'ancien bloc intact si échec.
		return NULL;
	}
	if (ptr)
	{
		copy_size = (old_size < new_size) ? old_size : new_size;
		ft_memcpy(new_ptr, ptr, copy_size);

		if (free_flag)
			free(ptr);
	}

	return new_ptr;
}

