/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 16:34:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 17:19:32 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_getline(const int fd, char **tab)
{
	char	buff[BUFF_SIZE + 1];
	char	*temp;
	int		ret;

	ret = 1;
	while (!ft_strchr(*tab, '\n') && ret > 0)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[ret] = '\0';
			if (!(temp = ft_strjoin(*tab, buff)))
				return (-1);
			free(*tab);
			*tab = temp;
		}
	}
	return (ret);
}

static	int		ft_newline(char **tab, char **line)
{
	int		i;
	char	*temp;
	int		newl;

	i = 0;
	newl = 0;
	if (!(*tab)[0])
	{
		*line = NULL;
		return (0);
	}
	while ((*tab)[i] && (*tab)[i] != '\n')
		i++;
	if ((*tab)[i] == '\n')
		newl = 1;
	*line = ft_strsub(*tab, 0, i);
	if (!(temp = ft_strsub(*tab, i + newl, ft_strlen(*tab))))
		return (-1);
	*tab = ft_strcpy(*tab, temp);
	free(temp);
	return (0);
}

static	t_glist	*find_fd(t_glist **lst, const int fd)
{
	while ((*lst)->next)
	{
		if ((*lst)->fd == fd)
			return (*lst);
		if ((*lst)->next)
			*lst = (*lst)->next;
	}
	if ((*lst)->fd == fd)
		return (*lst);
	if (!((*lst)->next = malloc(sizeof(t_glist))))
		return (NULL);
	(*lst)->next->fd = fd;
	(*lst)->next->next = NULL;
	if (!((*lst)->next->line = ft_strnew(0)))
		return (NULL);
	return ((*lst)->next);
}

int				get_next_line(const int fd, char **line)
{
	static t_glist	*lst = NULL;
	t_glist			*begin;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!lst)
	{
		if (!(lst = malloc(sizeof(t_glist))))
			return (-1);
		lst->fd = fd;
		if (!(lst->line = ft_strnew(0)))
			return (-1);
		lst->next = NULL;
	}
	begin = lst;
	if (!(lst = find_fd(&lst, fd)))
		return (-1);
	if (ft_getline(fd, &lst->line) == -1)
		return (-1);
	if (ft_newline(&lst->line, line) == -1)
		return (-1);
	lst = begin;
	if (*line)
		return (1);
	return (0);
}
