/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   option_l2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 14:28:28 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 14:33:46 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Permet de gerer les dates de moins de 6 mois
** ainsi que l'option -u
*/

void	more_6_month(struct stat *sb, int option, char (*temps)[12])
{
	int i;
	int rtime;
	int utime;

	i = 0;
	rtime = time(NULL) - sb->st_mtime;
	utime = time(NULL) - sb->st_atime;
	while (i <= 5)
	{
		!U ? (*temps)[i] = ctime(&sb->st_mtime)[4 + i] : 0;
		U ? (*temps)[i] = ctime(&sb->st_atime)[4 + i] : 0;
		i++;
	}
	if ((U && utime >= MOIS_6) || (!U && rtime >= MOIS_6))
		(*temps)[i++] = ' ';
	while (i <= 11)
	{
		rtime < MOIS_6 && !U ? (*temps)[i] = ctime(&sb->st_mtime)[4 + i] : 0;
		utime < MOIS_6 && U ? (*temps)[i] = ctime(&sb->st_atime)[4 + i] : 0;
		rtime >= MOIS_6 && !U ? (*temps)[i] = ctime(&sb->st_mtime)[12 + i] : 0;
		utime >= MOIS_6 && U ? (*temps)[i] = ctime(&sb->st_atime)[12 + i] : 0;
		i++;
	}
}
