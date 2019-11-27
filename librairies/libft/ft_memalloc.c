/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 10:51:01 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 13:20:43 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char *p;

	if (!(p = (void*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (size > 0)
	{
		p[size] = 0;
		size--;
	}
	p[size] = 0;
	return ((void*)p);
}
