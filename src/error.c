/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 13:45:02 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 17:22:41 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	usage(char c)
{
	ft_printf("ls: illegal option -- %c\n", c);
	ft_printf("usage: ls [-%s][file ...]\n", LIST_OPTION);
	exit(1);
}

int		error(char *s)
{
	ft_printf("ft_ls: %s: ", s);
	s = ft_strchr(strerror(errno), ':');
	perror(s);
	return (-1);
}

int		no_name(char *s)
{
	ft_printf("ft_ls: %s: ", s);
	ft_printf("No such file or directory\n");
	return (-1);
}
