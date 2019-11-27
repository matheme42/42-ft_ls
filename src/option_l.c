/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   option_l.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/08 16:15:50 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 14:29:39 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** permet d'attribuer une lettre en fonction du type de fichier
** necessaire pour le module ci-dessous (file_right(long right, int type))
*/

static char	select_type(int type)
{
	char c;

	c = '-';
	type == DIRECTORY ? c = 'd' : 0;
	type == LINK ? c = 'l' : 0;
	type == CHARACTER_DEVISE ? c = 'c' : 0;
	type == BLOCK_DEVISE ? c = 'b' : 0;
	type == SOCKET_LINK ? c = 's' : 0;
	type == NAME_PIPE ? c = 'p' : 0;
	return (c);
}

/*
** permet d'ecrire les droits et le type de fichier au format
** -rwxrwxrwx
*/

static void	file_right(long right, int type, int i)
{
	char	law[11];
	char	*s;

	ft_memset((void*)law, '-', 10);
	s = ft_itoo(right);
	i = ft_strlen(s);
	law[0] = select_type(type);
	s[i - 3] - '0' & 4 ? law[1] = 'r' : 0;
	s[i - 3] - '0' & 2 ? law[2] = 'w' : 0;
	s[i - 3] - '0' & 1 ? law[3] = 'x' : 0;
	s[i - 2] - '0' & 4 ? law[4] = 'r' : 0;
	s[i - 2] - '0' & 2 ? law[5] = 'w' : 0;
	s[i - 2] - '0' & 1 ? law[6] = 'x' : 0;
	s[i - 1] - '0' & 4 ? law[7] = 'r' : 0;
	s[i - 1] - '0' & 2 ? law[8] = 'w' : 0;
	s[i - 1] - '0' & 1 ? law[9] = 'x' : 0;
	s[i - 4] - '0' & 1 && law[9] == '-' ? law[9] = 'T' : 0;
	s[i - 4] - '0' & 1 && law[9] == 'x' ? law[9] = 't' : 0;
	s[i - 4] - '0' & 2 && law[6] == '-' ? law[6] = 'S' : 0;
	s[i - 4] - '0' & 2 && law[6] == 'x' ? law[6] = 's' : 0;
	s[i - 4] - '0' & 4 && law[3] == '-' ? law[3] = 'S' : 0;
	s[i - 4] - '0' & 4 && law[3] == 'x' ? law[3] = 's' : 0;
	law[10] = '\0';
	free(s);
	ft_putstr(law);
}

/*
** ce petit module permet d'afficher simplement la precense ou non
** d'attribut étendu ou type etendu
** on les symbolise avec un @ et +
*/

static int	extends_attribute(char *path)
{
	int retn;

	retn = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (retn > 0)
	{
		ft_putchar('@');
		return (1);
	}
	if (acl_get_file(path, ACL_TYPE_EXTENDED) != NULL)
	{
		ft_putchar('+');
		return (1);
	}
	return (0);
}

static void	majeur_mineur_or_size(t_file *file, t_max *max)
{
	long major;
	long minor;

	if (file->type != CHARACTER_DEVISE && file->type != BLOCK_DEVISE)
	{
		insert_space(max->size - ft_nbrlen(file->sb->st_size));
		ft_printf("%llu ", (long long)file->sb->st_size);
	}
	else
	{
		major = file->sb->st_rdev;
		minor = file->sb->st_rdev;
		while ((major / 256) > 0)
			major = major / 256;
		minor = minor % 256;
		insert_space(max->major - ft_nbrlen(major));
		ft_printf("% d, ", major);
		insert_space(max->minor - ft_nbrlen(minor));
		ft_printf("%d ", minor);
	}
}

/*
** permet d'ecrite au format de l'option -l
** de la fontion ls
** contient toutes les securité necessaire
*/

void		option_l(t_file *file, t_max *max, int option)
{
	struct passwd	*user;
	struct group	*group;
	char			temps[12];

	user = getpwuid(file->sb->st_uid);
	group = getgrgid(file->sb->st_gid);
	more_6_month(file->sb, option, &temps);
	file_right((unsigned long)file->sb->st_mode, file->type, 0);
	insert_space(2 - extends_attribute(file->path));
	insert_space(max->link - ft_nbrlen(file->sb->st_nlink));
	ft_printf("%hd ", file->sb->st_nlink);
	user ? ft_printf("%s  ", user->pw_name) : 0;
	!user ? ft_printf("%d  ", file->sb->st_uid) : 0;
	user ? insert_space(max->user - ft_strlen(user->pw_name)) : 0;
	!user ? insert_space(max->user - ft_nbrlen(file->sb->st_uid)) : 0;
	group ? ft_printf("%s  ", group->gr_name) : 0;
	!group ? ft_printf("%d  ", file->sb->st_gid) : 0;
	group ? insert_space(max->group - ft_strlen(group->gr_name)) : 0;
	!group ? insert_space(max->group - ft_nbrlen(file->sb->st_gid)) : 0;
	majeur_mineur_or_size(file, max);
	ft_printf("%.12s ", temps);
}
