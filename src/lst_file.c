/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_file.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/01 16:26:13 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 19:47:33 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** permet d'obtenir le type d'un fichier
**   FILES				100000
**   LINK				120000
**   DIRECTORY			40000
**   CHARACTER_DEVISE	20000
**   BLOCK_DEVISE		60000
**   NAME_PIPE			10000
**   SOCKET_LINK		140000
*/

static int		inspect_type_of_file(struct stat *sb)
{
	int	mode;

	if (sb == NULL)
		return (0);
	mode = ft_deci_to_octo((long)sb->st_mode & S_IFMT);
	return (mode);
}

/*
** creer un nouveau maillon de type t_list
** affecte les valeur de la liste grace a ceux passé en parametre
*/

static t_file	*new_lstfile(t_file *prev, char *m, char *p)
{
	t_file *maillon;

	if (!(maillon = malloc(sizeof(t_file))))
		return (NULL);
	maillon->next = NULL;
	maillon->prev = prev;
	maillon->sb = open_file(p);
	maillon->path = ft_strdup(p);
	maillon->name = ft_strdup(m);
	maillon->type = inspect_type_of_file(maillon->sb);
	return (maillon);
}

/*
** permet de liberer une t_list est son contenu
*/

void			free_list(t_file *begin)
{
	t_file *tmp;

	while (begin)
	{
		tmp = begin->next;
		begin->sb ? free(begin->sb) : 0;
		begin->path ? free(begin->path) : 0;
		begin->path ? free(begin->name) : 0;
		free(begin);
		begin = tmp;
	}
}

/*
** permet de stocker les differents fichier dans une liste t_file à
** partir D'UN DIRECTORY !!!!!!!!!!!.
** la fonction transmet ensuite un pointeur sur le premier maillon de cette
** nouvelle chaine
** ATTENTION = le premier maillon est toujours vide
*/

t_file			*stock_file_directory(char *path)
{
	DIR				*dirp;
	struct dirent	*files;
	char			*tmp;
	t_file			*file;
	t_file			*begin;

	dirp = opendir(path);
	if (dirp == NULL)
		return (NULL);
	file = new_lstfile(NULL, NULL, NULL);
	begin = file;
	while ((files = readdir(dirp)) != NULL)
	{
		tmp = add_segment_path(path, files->d_name);
		file->next = new_lstfile(file, files->d_name, tmp);
		file = file->next;
		free(tmp);
	}
	closedir(dirp);
	return (begin);
}

/*
** permet de stocker les differents fichier dans une liste t_file à
** partir DES ARGUMENT !!!!!!!!!!.
** la fonction transmet ensuite un pointeur sur le premier maillon de cette
** nouvelle chaine
** ATTENTION = le premier maillon est toujours vide
*/

t_file			*stock_file_av(char **av, char *path)
{
	int			i;
	char		*tmp;
	t_file		*file;
	t_file		*begin;

	i = 0;
	file = new_lstfile(NULL, NULL, NULL);
	begin = file;
	while (av[i])
	{
		if (av[i][0] == '/')
			tmp = ft_strdup(av[i]);
		else
			tmp = add_segment_path(path, av[i]);
		file->next = new_lstfile(file, av[i], tmp);
		file = file->next;
		i++;
		free(tmp);
	}
	return (begin);
}
