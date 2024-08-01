/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deep_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:19:56 by mzurera-          #+#    #+#             */
/*   Updated: 2024/07/17 14:59:14 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_deep_free(void **ptr, unsigned int depth)
{
	unsigned int	i;
	void			**mem;

	if (ptr == NULL || *ptr == NULL)
		return (NULL);
	if (depth <= 0)
		return (NULL);
	mem = (void **) *ptr;
	i = 0;
	while (depth > 1 && mem[i] != NULL)
	{
		if (depth > 2)
			ft_deep_free((void **)(mem + i), depth - 1);
		free(mem[i]);
		i++;
	}
	free(mem);
	*ptr = NULL;
	return (NULL);
}
