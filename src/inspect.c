/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   inspect.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 15:33:43 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 03:48:10 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**  1024 512 256 128  64  32  16   8   4   2   1
**    f   1   u   G    p   s   l   R   a   r   t
**    0   0   0   0    0   0   0   0   0   0   0
*/

static void	recursive_dir(t_file *begin, int option, US ws_col)
{
	t_file	*f;
	int		ghost_file;

	f = begin;
	while (f && f->prev)
	{
		ghost_file = get_ghost_file(f->name);
		if (f->type == DIRECTORY && ghost_file != 2 && (ghost_file != 1 || A))
		{
			ft_printf("\n%s:\n", f->path);
			(!L || UN) && !RR ? ft_printf("%s:\n", begin->name) : 0;
			inspect_dir(f->name, option, f->path, ws_col);
		}
		!R ? f = f->next : 0;
		R ? f = f->prev : 0;
	}
}

static void	inspect_dir_browse_module(t_file *file, t_max *lst_max, int option)
{
	while (file && file->prev)
	{
		if (file->sb && (file->name[0] != '.' || A))
			inspect_file(file, lst_max, option);
		!R ? file = file->next : 0;
		R ? file = file->prev : 0;
	}
}

void		inspect_dir(char *dir_name, int option, char *path, US ws_col)
{
	t_file	*file;
	t_file	*tmp;
	t_file	*begin;
	t_max	*lst_max;

	if (!(begin = stock_file_directory(path)))
	{
		error(dir_name);
		return ;
	}
	file = begin->next;
	lst_max = get_len_of_file_in_directory(file, option);
	file = sorting(file, option);
	tmp = file;
	if ((L && !UN && lst_max->nb_file) || (!L && S && lst_max->nb_file))
		ft_printf("total %d\n", lst_max->block_size_number);
	L || UN ? inspect_dir_browse_module(file, lst_max, option) : 0;
	!L && !UN ? display_c(ws_col, tmp, lst_max, option) : 0;
	RR ? recursive_dir(tmp, option, ws_col) : 0;
	free(lst_max);
	free_list(begin);
}

void		module_g(char *s, int type, int mode)
{
	char *n;

	if (type == FILES)
	{
		n = ft_itoa(ft_deci_to_octo(mode) - type);
		if (ft_strchr(n, '7'))
			ft_printf("%s%s", EXECUTABLE, s);
		else
			ft_putstr(s);
		free(n);
	}
	type == NAME_PIPE ? ft_printf("%s%s", NAME_PIPE_COLOR, s) : 0;
	type == DIRECTORY ? ft_printf("%s%s", DIRECTORY_COLOR, s) : 0;
	type == CHARACTER_DEVISE ? ft_printf("%s%s", CHARACTER_DEVISE_COLOR, s) : 0;
	type == BLOCK_DEVISE ? ft_printf("%s%s", BLOCK_DEVISE_COLOR, s) : 0;
	type == LINK ? ft_printf("%s%s", LINK_COLOR, s) : 0;
	ft_putstr(DEFAULT_COLOR);
}

void		inspect_file(t_file *file, t_max *max, int option)
{
	char	tmp[100];

	S ? insert_space(max->block_size - ft_nbrlen(file->sb->st_blocks)) : 0;
	S ? ft_printf("%lld ", (long long)file->sb->st_blocks) : 0;
	L && !UN ? option_l(file, max, option) : 0;
	!G ? ft_printf("%s", file->name) : 0;
	G ? module_g(file->name, file->type, file->sb->st_mode) : 0;
	if (L && !UN && file->type == LINK)
	{
		tmp[readlink(file->path, tmp, 100)] = '\0';
		ft_printf(" -> %s", tmp);
	}
	P && file->type == DIRECTORY ? ft_putchar('/') : 0;
	L || UN ? ft_putchar('\n') : 0;
}
