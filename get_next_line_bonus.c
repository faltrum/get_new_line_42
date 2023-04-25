/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:12:54 by oseivane          #+#    #+#             */
/*   Updated: 2023/02/23 14:25:54 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_cajon(int fd, char *cajon)
{
	char	*posit;
	size_t	bytes_read;

	posit = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!posit)
		return (NULL);
	bytes_read = -1;
	while (bytes_read != 0 && !ft_strchr(cajon, '\n'))
	{
		bytes_read = read(fd, posit, BUFFER_SIZE);
		if ((int)bytes_read == -1)
		{
			free(posit);
			free(cajon);
			return (NULL);
		}
		posit[bytes_read] = '\0';
		cajon = ft_strjoin(cajon, posit);
	}
	free(posit);
	return (cajon);
}

char	*extract_line(char *cajon)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	if (!cajon || !cajon[0])
		return (NULL);
	len = ft_strchr_index(cajon, '\n');
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	while (i <= len)
	{
		line[i] = cajon[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*overwrite_cajon(char *cajon)
{
	char	*overwrite;
	int		i;
	int		j;

	if (!cajon)
		return (NULL);
	i = ft_strchr_index(cajon, '\n');
	j = 0;
	if (!cajon[i])
	{
		free(cajon);
		return (NULL);
	}
	overwrite = malloc(sizeof(char) * ((ft_strlen(cajon) - i) + 1));
	if (!overwrite)
		return (NULL);
	i++;
	while (cajon[i] != '\0')
		overwrite[j++] = cajon[i++];
	overwrite[j] = '\0';
	free(cajon);
	return (overwrite);
}

char	*get_next_line(int fd)
{
	static char		*cajon[4096];
	char			*line;		

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cajon[fd] = extract_cajon(fd, cajon[fd]);
	if (!cajon[fd])
		return (NULL);
	line = extract_line(cajon[fd]);
	cajon[fd] = overwrite_cajon(cajon[fd]);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("TEST/t.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s\n", str);
	free(str);
	close(fd);
}
*/
