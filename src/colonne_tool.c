/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   colonne_tool.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 08:29:57 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 18:18:24 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			*go_next_go_prev(int option, t_file *f, int n, int filtre)
{
	while (n--)
	{
		!R && f ? f = f->next : 0;
		R && f->prev ? f = f->prev : 0;
		if (f && f->prev && filtre == 1 && (f->name[0] == '.' && !A))
			n++;
		if (f && f->prev && filtre == 2 && (!f->sb || f->type == DIRECTORY))
			n++;
	}
	return (f);
}

/*
** permet de connaitre le nombre de ligne utilisé par les fichiers en
** connaissant a l'avance le nombre de fichier
*/

static int		get_maxline(int nb_file, unsigned short ws_col, int nb_space)
{
	int		maxline;
	int		nb_max_file_on_line;

	maxline = 1;
	nb_max_file_on_line = ws_col / nb_space;
	if (nb_max_file_on_line == 0)
		nb_max_file_on_line++;
	if (ws_col % nb_space < 7 && nb_max_file_on_line > 1)
		nb_max_file_on_line--;
	while (nb_file > maxline * nb_max_file_on_line)
		maxline++;
	return (maxline);
}

/*
** permet de connaitre le nombre de colonne utilisé par les fichiers en
** connaissant a l'avance le nombre de fichier
*/

static int		get_maxcol(int nb_file, unsigned short ws_col, int nb_space)
{
	float	maxcol;
	int		max_line;

	max_line = get_maxline(nb_file, ws_col, nb_space);
	maxcol = nb_file / max_line;
	if (nb_file % max_line)
		return (maxcol + 1);
	return (maxcol);
}

/*
** moc = module_option_colonne
** lors de l'ajout d'option qui modifie la taille des colonnes
** des changements sont a faire ici mais egalement sur la taille du nom
** des fichiers
** dans lst_max
*/

int				moc(t_file *file, t_max *lst_max, int option, t_col c)
{
	int n;

	n = c.s - ft_strlen(file->name) + 1;
	S ? n -= lst_max->block_size : 0;
	P && file->type == DIRECTORY ? n -= 1 : 0;
	return (n);
}

/*
** permet de recuperer les valeurs necessaires pour l'affichage colonne
*/

void			init_t_col(t_col *c, US ws_col, t_max *lst_max)
{
	c->i_file = 0;
	c->s = lst_max->name;
	c->maxcol = get_maxcol(lst_max->nb_file, ws_col, lst_max->name + 1);
	c->maxline = get_maxline(lst_max->nb_file, ws_col, lst_max->name + 1);
	c->line_in_max_col = lst_max->nb_file % c->maxline;
}
