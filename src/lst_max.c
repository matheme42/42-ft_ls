/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_max.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 14:49:03 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 16:11:22 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Permet de creer un nouveau maillon t_max et de l'initialiser a NULL
*/

static t_max	*new_lstmax(void)
{
	t_max *maillon;

	if (!(maillon = malloc(sizeof(t_file))))
		return (NULL);
	maillon->next = NULL;
	maillon->link = 0;
	maillon->size = 0;
	maillon->user = 0;
	maillon->group = 0;
	maillon->name = 0;
	maillon->major = 0;
	maillon->minor = 0;
	maillon->block_size = 0;
	maillon->nb_file = 0;
	maillon->block_size_number = 0;
	return (maillon);
}

/*
** Permet de recuperer la longueur maximale que prennes le nom du user
** et du groupe
*/

static t_max	*get_len_of_name_group(t_max *lst_max, t_file *file)
{
	struct passwd	*user;
	struct group	*group;
	int				user_len;
	int				group_len;

	user = getpwuid(file->sb->st_uid);
	group = getgrgid(file->sb->st_gid);
	user ? user_len = ft_strlen(user->pw_name) : 0;
	group ? group_len = ft_strlen(group->gr_name) : 0;
	!user ? user_len = ft_nbrlen(file->sb->st_uid) : 0;
	!group ? group_len = ft_nbrlen(file->sb->st_gid) : 0;
	user && user_len > lst_max->user ? lst_max->user = user_len : 0;
	group && group_len > lst_max->group ? lst_max->group = group_len : 0;
	return (lst_max);
}

/*
** mineur
** majeur
*/

static t_max	*majeur_mineur_len(t_max *lst_max, t_file *file)
{
	long	major;
	long	minor;
	int		major_len;
	int		minor_len;

	major = file->sb->st_rdev;
	minor = file->sb->st_rdev;
	while ((major / 256) > 0)
		major = major / 256;
	minor = minor % 256;
	major_len = ft_nbrlen((long long)major);
	minor_len = ft_nbrlen((long long)minor);
	major_len > lst_max->major ? lst_max->major = major_len : 0;
	minor_len > lst_max->minor ? lst_max->minor = minor_len : 0;
	return (lst_max);
}

/*
** Permet de recuperer la longueur maximale que prennes les Entier
** liés aux links et a la size (octets)
*/

static t_max	*get_file_len(t_max *max, t_file *file)
{
	int				size;
	int				link;
	int				blocks_size;
	int				name;

	if (file->type == CHARACTER_DEVISE || file->type == BLOCK_DEVISE)
		max = majeur_mineur_len(max, file);
	name = ft_strlen(file->name);
	link = ft_nbrlen((long long)file->sb->st_nlink);
	!max->major && !max->minor ? size = ft_nbrlen(file->sb->st_size) : 0;
	max->major || max->minor ? size = max->major + max->minor + 2 : 0;
	blocks_size = ft_nbrlen((long long)file->sb->st_blocks);
	name > max->name ? max->name = name : 0;
	link > max->link ? max->link = link : 0;
	size > max->size ? max->size = size : 0;
	blocks_size > max->block_size ? max->block_size = blocks_size : 0;
	max->block_size_number += (long long)file->sb->st_blocks;
	return (max);
}

/*
** Cette Fonction permet de donner les information pour redresser l'affichage
** et fait apparaitre ainsi des colonne bien precise
** AVANT :
** 0 drwxr-xr-x7 matheme student 238 Feb 26 15:09 .
** 0 drwxr-xr-x4 matheme student 136 Feb 26 15:01 ..
** 8 -rw-r--r--1 matheme student 8 Feb 26 14:59 auteur
** 0 drwxr-xr-x3 matheme student 102 Feb 27 12:00 include
** 96 -rw-r--r--1 matheme student 48200 Feb 26 15:09 libftprintf.a
** 8 -rw-r--r--@1 matheme student 1221 Feb 26 14:59 Makefile
** 0 drwxr-xr-x7 matheme student 238 Feb 26 14:59 src
**  APRES :
** total 112
** drwxr-xr-x  7 matheme  student    238 Feb 26 15:09 .
** drwxr-xr-x  4 matheme  student    136 Feb 26 15:01 ..
** -rw-r--r--  1 matheme  student      8 Feb 26 14:59 auteur
** drwxr-xr-x  3 matheme  student    102 Feb 27 12:00 include
** -rw-r--r--  1 matheme  student  48200 Feb 26 15:09 libftprintf.a
** -rw-r--r--@ 1 matheme  student   1221 Feb 26 14:59 Makefile
** drwxr-xr-x  7 matheme  student    238 Feb 26 14:59 src
*/

t_max			*get_len_of_file_in_directory(t_file *file, int option)
{
	t_max	*lst_max;
	t_max	*begin;

	lst_max = new_lstmax();
	begin = lst_max;
	while (file)
	{
		if (file->sb)
		{
			if (!get_ghost_file(file->name) || A)
			{
				lst_max = get_len_of_name_group(lst_max, file);
				lst_max = get_file_len(lst_max, file);
			}
		}
		(file->name[0] != '.' || A) ? lst_max->nb_file += 1 : 0;
		file = file->next;
	}
	P ? lst_max->name += 1 : 0;
	S ? lst_max->name += lst_max->block_size : 0;
	return (begin);
}
