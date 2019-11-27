/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   colonne.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 14:35:40 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 19:59:02 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int			display_c_m(t_file *file, t_max *max, int option, t_col c)
{
	int	i;

	i = 0;
	while (file && file->prev)
	{
		if (file->name[0] == '.' && !A)
			file = go_next_go_prev(option, file, 1, 1);
		if (file && file->prev)
		{
			i++;
			file->sb ? inspect_file(file, max, option) : 0;
			i % c.maxcol ? insert_space(moc(file, max, option, c)) : 0;
			!(i % c.maxcol) ? ft_putchar('\n') : 0;
		}
		file = go_next_go_prev(option, file, c.maxline, 1);
	}
	return (i);
}

void		display_c(US ws_col, t_file *begin, t_max *max, int option)
{
	t_col	c;

	init_t_col(&c, ws_col, max);
	if (begin && (begin->name[0] == '.' && !A))
		begin = go_next_go_prev(option, begin, 1, 1);
	while (c.i_file < max->nb_file)
	{
		c.i_file += display_c_m(begin, max, option, c);
		if (c.i_file / c.maxcol == c.line_in_max_col && !(c.i_file % c.maxcol))
			c.maxcol = c.maxcol - 1;
		begin = go_next_go_prev(option, begin, 1, 1);
	}
}

static int	get_no_file(t_file *f, int option, t_max *max)
{
	int i;

	i = 0;
	max->name = 0;
	while (f && f->prev)
	{
		!f->sb ? no_name(f->name) : 0;
		if (f && f->prev && (f->name[0] != '.' || A))
		{
			!f->sb ? i += 1 : 0;
			f->type == DIRECTORY && f->sb ? i += 1 : 0;
			if (f->type != DIRECTORY && f->sb)
			{
				if ((int)ft_strlen(f->name) > max->name)
					max->name = ft_strlen(f->name);
			}
		}
		f = go_next_go_prev(option, f, 1, 0);
	}
	P ? max->name += 1 : 0;
	S ? max->name += max->block_size : 0;
	return (i);
}

static int	display_c_avm(t_file *f, t_max *max, int option, t_col c)
{
	int i;

	i = 0;
	while (f && f->prev)
	{
		if (f && f->prev && f->sb && f->type != DIRECTORY
			&& f->type != LINK && (f->name[0] != '.' || A))
		{
			inspect_file(f, max, option);
			++i % c.maxcol ? insert_space(moc(f, max, option, c)) : 0;
			!(i % c.maxcol) ? ft_putchar('\n') : 0;
		}
		f = go_next_go_prev(option, f, c.maxline, 2);
	}
	return (i);
}

int			display_c_av(US ws_col, t_file *begin, t_max *max, int option)
{
	t_col	c;
	int		i;

	i = 0;
	max->nb_file -= get_no_file(begin, option, max);
	if (begin && begin->name[0] == '.' && !A)
		begin = go_next_go_prev(option, begin, 1, 0);
	init_t_col(&c, ws_col, max);
	if (begin && (!begin->sb || begin->type == DIRECTORY))
		begin = go_next_go_prev(option, begin, 1, 2);
	while (c.i_file < max->nb_file)
	{
		i = display_c_avm(begin, max, option, c);
		c.i_file += c.maxcol;
		c.i_file / c.maxcol == c.line_in_max_col ? c.maxcol = c.maxcol - 1 : 0;
		begin = go_next_go_prev(option, begin, 1, 2);
	}
	return (i);
}
