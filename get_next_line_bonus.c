/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:47:22 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/04/12 19:18:02 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join(char *buff, char *stash)
{
	int		i;
	int		j;
	char	*new_buff;

	i = 0;
	j = 0;
	new_buff = (char *)malloc(sizeof(char) * ft_strlen(buff)
			+ ft_strlen_after_one(stash, '\0') + 1);
	while (buff[i])
	{
		new_buff[i] = buff[i];
		i++;
	}
	while (stash[j] == -1)
		j++;
	while (stash[j] && stash[j] != -1)
	{
		new_buff[i] = stash[j];
		i++;
		j++;
	}
	new_buff[i] = '\0';
	init_and_put_one(stash, '\0');
	free (buff);
	return (new_buff);
}

char	*ft_join_new_line(char *buff, char *stash)
{
	int		i;
	int		j;
	char	*new_buff;

	i = -1;
	j = 0;
	new_buff = (char *)malloc(sizeof(char) * ft_strlen(buff)
			+ ft_strlen_after_one(stash, '\n') + 2);
	while (buff[++i])
		new_buff[i] = buff[i];
	while (stash[j] == -1)
		j++;
	while (stash[j] != '\n')
	{
		new_buff[i] = stash[j];
		i++;
		j++;
	}
	new_buff[i] = '\n';
	i++;
	new_buff[i] = '\0';
	init_and_put_one(stash, '\n');
	free (buff);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	stash[BUFFER_SIZE][1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * 1);
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	while (1)
	{
		if (ft_one(stash[fd]) == 0 && read(fd, stash[fd], BUFFER_SIZE) == 0)
			break ;
		if (ft_check_new_line(stash[fd]) == 0)
			buff = ft_join(buff, stash[fd]);
		if (ft_check_new_line(stash[fd]) == 1)
		{
			buff = ft_join_new_line(buff, stash[fd]);
			break ;
		}
	}
	if (buff[0] == '\0')
		return (free(buff), NULL);
	return (buff);
}

int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	int		fd3;
	char	*t;
	char	*u;
	char	*v;
	int		i;

	i = 0;
	fd = open("text1.txt", O_RDONLY);
	fd1 = open("text2.txt", O_RDONLY);
	fd2 = open("text3.txt", O_RDONLY);
	t = malloc(sizeof(char) * 1);
	t[0] = '\0';
	u = malloc(sizeof(char) * 1);
	u[0] = '\0';
	v = malloc(sizeof(char) * 1);
	v[0] = '\0';
	
	while (t != NULL)
	{
		free(t);
		free (u);
		free (v);
		printf("APPEL %d :\n", i);
		t = get_next_line(fd);
		printf("%s", t);
		printf("APPEL %d :\n", i);
		u = get_next_line(fd1);
		printf("%s", u);
		printf("APPEL %d :\n", i);
		v = get_next_line(fd2);
		printf("%s", v);
		i++;
	}
	free(t);
	free (u);
	free (v);
}
