/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 14:43:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 14:50:19 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** permet de savoir si le fichier est un fichier cacher et plus precisement si
** il s'agit des fichier . ou ..
** valeur de retour : 0 = non cacher 1 = cacher != . && != .. 2 = . || ..
*/

int			get_ghost_file(char *name)
{
	if (name[0] == '.')
	{
		if (name[1] == '.')
		{
			if (name[2] == '\0')
				return (2);
		}
		if (name[1] == '\0')
			return (2);
		return (1);
	}
	return (0);
}

/*
** permet de rajouter un segment de chemin au chemin principale
*/

char		*add_segment_path(char *path, char *segment)
{
	char	*path_tmp;

	path_tmp = ft_strjoin(path, "/");
	path = ft_strjoin(path_tmp, segment);
	free(path_tmp);
	return (path);
}

/*
** permet d'ouvrir un fichier et d'envoyer une structure contenant
**  les informations à propos de ce fichier
*/

struct stat	*open_file(char *path)
{
	struct stat		*sb;
	struct stat		*ln;

	sb = malloc(sizeof(struct stat));
	if (stat(path, sb) == -1)
	{
		free(sb);
		return (NULL);
	}
	ln = malloc(sizeof(struct stat));
	if (lstat(path, ln) == -1)
	{
		free(sb);
		free(ln);
		return (NULL);
	}
	if ((ln->st_mode & S_IFMT) != (sb->st_mode & S_IFMT))
	{
		free(sb);
		return (ln);
	}
	free(ln);
	return (sb);
}

/*
** permet d'inserer un certain nombre d'espace
*/

void		insert_space(int n)
{
	if (n > 0)
	{
		ft_putchar(' ');
		insert_space(n - 1);
	}
}

/*
** permet de swap 2 maillons de type t_file
*/

t_file		*swap_file(t_file *a, t_file *b)
{
	if (b->next)
		b->next->prev = a;
	if (a->prev)
		a->prev->next = b;
	b->prev = a->prev;
	a->next = b->next;
	b->next = a;
	a->prev = b;
	return (b->prev);
}
