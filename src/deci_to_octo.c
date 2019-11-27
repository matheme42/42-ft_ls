/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   deci_to_octo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/08 17:00:22 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 13:49:06 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	nbrlen_octo(long long n)
{
	size_t	t;

	t = 1;
	if (n > 0)
		n = -n;
	while (n / ft_power(8, t) <= -1)
		t++;
	return (t);
}

static char		*ft_putnbr_in_octo(unsigned long long nb, int i, char *s)
{
	const char base[8] = "01234567";

	if (nb / 8 > 0)
		s = ft_putnbr_in_octo(nb / 8, i - 1, s);
	s[i] = base[nb % 8];
	return (s);
}

char			*ft_itoo(int n)
{
	char	*s;
	int		size;

	size = nbrlen_octo(n);
	if (!(s = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	s = ft_putnbr_in_octo(n, size - 1, s);
	s[size] = '\0';
	return (s);
}

int				ft_deci_to_octo(int n)
{
	char	*s;

	if (!(s = ft_itoo(n)))
		return (0);
	n = ft_atoi(s);
	free(s);
	return (n);
}
