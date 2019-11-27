/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 11:55:47 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 14:30:00 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
**  1024 512 256 128  64  32  16   8   4   2   1
**    f   1   u   G    p   s   l   R   a   r   t
**    0   0   0   0    0   0   0   0   0   0   0
*/

/*
** help for option's comprehention
*/

# define F (option & 1024)
# define UN (option & 512)
# define U (option & 256)
# define G (option & 128)
# define P (option & 64)
# define S (option & 32)
# define L (option & 16)
# define RR (option & 8)
# define A (option & 4)
# define R (option & 2)
# define T (option & 1)
# define LIST_OPTION "GRalprstu1"

/*
** help for type's comprehention
*/
# define FILES					100000
# define LINK					120000
# define DIRECTORY				40000
# define CHARACTER_DEVISE		20000
# define BLOCK_DEVISE			60000
# define NAME_PIPE				10000
# define SOCKET_LINK			140000

/*
** color use with the option -G
*/
# define DEFAULT_COLOR			"\e[0;49;37m"
# define NAME_PIPE_COLOR		"\e[0;49;33m"
# define DIRECTORY_COLOR		"\e[1;96m"
# define LINK_COLOR				"\e[35m"
# define CHARACTER_DEVISE_COLOR	"\e[43;34m"
# define BLOCK_DEVISE_COLOR		"\e[46;34m"
# define EXECUTABLE				"\e[31m"

/*
** the norme
*/
# define US unsigned short
# define MOIS_6 15778463

# include <errno.h>
# include <stdio.h>

/*
** allow the function of the libft
*/
# include "libft.h"

/*
** opendir
** readdir
**closedir
*/
# include <dirent.h>

/*
** time
** ctime
*/
# include <time.h>

/*
** stat
** lstat
*/
# include <sys/stat.h>

/*
** for the ids
*/
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

/*
** the typing
*/
# include <sys/types.h>

/*
** extends attribut @ et +
*/
# include <sys/acl.h>
# include <sys/xattr.h>

/*
** allow the possibility to create columns help by windows's size
*/
# include <sys/ioctl.h>

/*
** struct contaning main's informations and feature's information about
** files / directory / link / etc..
** containing in the same directory
*/

typedef struct		s_file
{
	char			*name;
	char			*path;
	struct stat		*sb;
	int				type;
	struct s_file	*prev;
	struct s_file	*next;

}					t_file;

/*
** struct contaning the information about MAX size that the main's information
** takes about files / directory / link / etc...
** containing in the same directory
** exemple : max size of the host name : max size of the octect file
** max size of the link : or allow's blocks
*/

typedef struct		s_maxlen
{
	int				link;
	int				size;
	int				user;
	int				group;
	int				block_size;
	int				block_size_number;
	int				name;
	int				nb_file;
	int				major;
	int				minor;
	struct s_maxlen	*next;

}					t_max;

typedef struct		s_col
{
	int				s;
	int				maxcol;
	int				line_in_max_col;
	int				maxline;
	int				i_file;

}					t_col;

/*
** at the same comportment of printf
*/
int					ft_printf(const char *format, ...);

int					ft_deci_to_octo(int n);
char				*ft_itoo(int n);
/*
******************************************************************************
*******************************FONCTION TOOL**********************************
******************************************************************************
*/

/*
** permet de rajouter un segment de chemin au chemin principale
*/
char				*add_segment_path(char *path, char *segment);

/*
** open a file and send a struct containing the information about the file
*/
struct stat			*open_file(char *path);

/*
** allows to insert a certain amount of space
*/
void				insert_space(int n);

/*
** allows to know if the file is a hide's file and
** more precisely if it is the file . or ..
** return value : 0 = visible 1 = hide != . && != .. 2 = . || ..
*/
int					get_ghost_file(char *name);

/*
** allow to swap 2 t_file's maillons
*/
t_file				*swap_file(t_file *a, t_file *b);

/*
******************************************************************************
***************THE INSPECTOR OF (FILE | DIRECTORY | ARG | ...)****************
******************************************************************************
*/

/*
** the inspector
*/
void				inspect_dir(char *dir_n, int opt, char *path, US ws);
void				inspect_file(t_file *file, t_max *lst_max, int option);

/*
******************************************************************************
***************************DISPLAY (COLUMNS | LINE)***************************
******************************************************************************
*/

/*
** permet d'afficher en colonne quand l'option -l et -1 ne sont pas activés
*/

void				display_c(US ws, t_file *f, t_max *lmax, int op);
int					display_c_av(US ws, t_file *f, t_max *lmax, int op);
int					moc(t_file *file, t_max *lst_max, int option, t_col c);
void				init_t_col(t_col *c, US ws_col, t_max *lst_max);
t_file				*go_next_go_prev(int option, t_file *file, int n, int flr);

/*
** permet de structurer l'affichage principale de l'option -l ou -1
** affichage ligne par ligne
*/
void				option_l(t_file *file, t_max *max, int option);
void				more_6_month(struct stat *sb, int option, char (*tmp)[12]);

/*
******************************************************************************
***********************FUCTION T_MAX (STOCK | NEW)****************************
******************************************************************************
*/

/*
** la fonction qui creer une t_max (voir ci-dessus) à partir d'une t_file
*/
t_max				*get_len_of_file_in_directory(t_file *file, int option);

/*
******************************************************************************
******************FUCTION LST_LIST (STOCK | NEW | FREE)***********************
******************************************************************************
*/

/*
** fonction pour supprimer une t_file en lui donnant le debut de la chaine
*/
void				free_list(t_file *begin);

/*
**stocke toutes les informations de fichier passer en parametre
*/
t_file				*stock_file_av(char **av, char *path);

/*
**stocke toutes les informations de fichier present dans un directory
*/
t_file				*stock_file_directory(char *path);

/*
******************************************************************************
***************************FUCTION FOR SORTING********************************
******************************************************************************
*/
t_file				*sorting(t_file *list, int option);

/*
******************************************************************************
*****************************FUCTION OPTION***********************************
******************************************************************************
*/

/*
** permet de recuperer les options de ls et renvoi un pointeur situé après
** les options
*/
char				**get_option(int ac, char **av, int *option);

/*
******************************************************************************
*****************************FUCTION D'ERROR**********************************
******************************************************************************
*/

/*
** permet de lancer le usage et de quitter le programme proprement
*/
void				usage(char c);

/*
** permet de lancer les erreurs systeme (ne quitte pas le programme)
*/
int					error(char *s);

int					no_name(char *s);
#endif
