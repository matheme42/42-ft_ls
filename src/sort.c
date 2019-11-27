/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/08 18:03:08 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 18:15:18 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** module de trie par date de dernier accès
*/

static t_file	*sort_module_u(t_file *current, t_file *next)
{
	if (current->sb->st_atime < next->sb->st_atime)
	{
		current = swap_file(current, next);
		if (current->prev)
			current = current->prev;
		if (current->prev)
			current = current->prev;
	}
	else if (current->sb->st_atime == next->sb->st_atime)
	{
		if (ft_strcmp(current->name, next->name) > 0)
		{
			current = swap_file(current, next);
			if (current->prev)
				current = current->prev;
			if (current->prev)
				current = current->prev;
		}
	}
	return (current);
}

/*
** module de trie par date de dernieres modifications
*/

static t_file	*sort_module_t(t_file *current, t_file *next)
{
	if (current->sb->st_mtime < next->sb->st_mtime)
	{
		current = swap_file(current, next);
		if (current->prev)
			current = current->prev;
		if (current->prev)
			current = current->prev;
	}
	else if (current->sb->st_mtime == next->sb->st_mtime)
	{
		if (ft_strcmp(current->name, next->name) > 0)
		{
			current = swap_file(current, next);
			if (current->prev)
				current = current->prev;
			if (current->prev)
				current = current->prev;
		}
	}
	return (current);
}

/*
** cette fonction permet de trier la list des fichier par rapport au temps
** pour fonctionner cette fonction a besoin de la fonction swap_file
** Cette fonction peut utiliser 2 modules differents
** - sort_module_t --> date de dernieres modifications
** - sort_module_u --> date de dernier accès
*/

static t_file	*sort_with_time(t_file *list, int option)
{
	while (list->next)
	{
		if (list->sb && list->next->sb)
		{
			U ? list = sort_module_u(list, list->next) : 0;
			!U ? list = sort_module_t(list, list->next) : 0;
		}
		list = list->next;
	}
	while (!R && list->prev->prev)
		list = list->prev;
	return (list);
}

/*
** cette fonction permet de trier la list des fichier par order ascii
** pour fonctionner cette fonction a besoin de la fonction swap_file
*/

static t_file	*sort_with_ascii(t_file *list, int option)
{
	while (list->next)
	{
		if (ft_strcmp(list->name, list->next->name) > 0)
		{
			list = swap_file(list, list->next);
			if (list->prev)
				list = list->prev;
			if (list->prev)
				list = list->prev;
		}
		list = list->next;
	}
	while (!R && list->prev->prev)
		list = list->prev;
	return (list);
}

/*
** à verifier quand meme
** le trie par temps segfault avec la commande
** ./ft_ls -lRt ../../../../../
*/

t_file			*sorting(t_file *list, int option)
{
	!T && !F ? list = sort_with_ascii(list, option) : 0;
	T && !F ? list = sort_with_time(list, option) : 0;
	return (list);
}
