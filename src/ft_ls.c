/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 11:58:34 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 20:00:02 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	inspect_av_link(t_file *f, t_max *lst_max, int option, US ws_col)
{
	return (0);
}

/*
** module pour lire tout les type de fichier sauf les directory
*/

static int	inspect_av_file(t_file *f, t_max *lst_max, int option, US ws_col)
{
	int i;

	i = 0;
	if (!L && !UN)
		return (display_c_av(ws_col, f, lst_max, option));
	while (f && f->prev)
	{
		!f->sb ? error(f->name) : 0;
		if (f->sb && f->type != DIRECTORY)
		{
			i++;
			f->sb ? inspect_file(f, lst_max, option) : 0;
		}
		!R ? f = f->next : 0;
		R ? f = f->prev : 0;
	}
	return (i);
}

/*
** permet de scruter tous les argument passé en parametre
*/

int			inspect_av(char **av, int option, char *path, US ws_col)
{
	t_file	*f;
	t_file	*begin;
	int		retn;
	t_max	*lst_max;

	begin = stock_file_av(av, path);
	f = begin->next;
	lst_max = get_len_of_file_in_directory(f, option);
	f = sorting(f, option);
	retn = inspect_av_file(f, lst_max, option, ws_col);
	while (f && f->prev)
	{
		if (f->sb && (f->type == DIRECTORY || f->type == LINK))
		{
			retn ? ft_putstr("\n") : 0;
			av[1] ? ft_printf("%s:\n", f->name) : 0;
			retn = 1;
			inspect_dir(f->name, option, f->name, ws_col);
		}
		!R ? f = f->next : 0;
		R ? f = f->prev : 0;
	}
	free(lst_max);
	free_list(begin);
	return (0);
}

/*
** la commande ft_ls
** ce referer au man de la fonction ls
*/

int			ft_ls(int ac, char **av, unsigned short ws_col)
{
	int		option;

	option = 0;
	ac == 0 ? inspect_dir(".", 0, ".", ws_col) : 0;
	ac != 0 ? av = get_option(ac, av, &option) : 0;
	!*av && ac != 0 ? inspect_dir(".", option, ".", ws_col) : 0;
	*av && ac != 0 ? inspect_av(av, option, ".", ws_col) : 0;
	return (0);
}

/*
** main du programme (appelle la fonction ft_ls)
** donne la taille actuelle de la fenetre au lancement de la fonction
*/

int			main(int ac, char **av)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ft_ls(ac - 1, &av[1], w.ws_col);
	return (0);
}
