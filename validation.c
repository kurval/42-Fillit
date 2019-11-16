/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzaiedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:44:18 by jzaiedma          #+#    #+#             */
/*   Updated: 2019/11/15 16:37:09 by jzaiedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*
** Cheks if tetrimino is right shape an returns 6 or 8.
** First if statement checks if # connects another # above
** second checks connection on the right side
** third one checks connection down
** and if statement checks connection on the left side.
** While checks connections of every '#' characters of
** one block.
*/

int	check_block_shape(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 16)
	{
		if (str[i] == '#')
		{
			if ((str[i - 4] == '#') && (i > 3))
				count++;
			if ((str[i + 1] == '#') && ((i + 1) % 4 != 0) && (i < 16))
				count++;
			if ((str[i + 4] == '#') && (i < 12))
				count++;
			if ((str[i - 1] == '#') && (i % 4 != 0) && (i != 0))
				count++;
		}
		i++;
	}
	return (count);
}

/*
** Checks that block includes right amount of '.' and '#' chars.
*/

int	check_block_chars(char *str)
{
	static int	block_count = 0;
	int			hashtags;
	int			dots;
	int			i;

	block_count++;
	hashtags = 0;
	dots = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dots++;
		if (str[i] == '#')
			hashtags++;
		i++;
	}
	if (dots == 12 && hashtags == 4)
	{
		check_block_shape(str);
		if (check_block_shape(str) != 8 && check_block_shape(str) != 6)
			return (0);
		return (1);
	}
	return (0);
}

/*
** Checks that rows are valid and creates a string from one block.
** This function also checks that block max is 26
*/

int	check_lines(char **str, char *line, int fd, int n)
{	
	int	count;

	count = 0;
	if (n == 26)
		return (0);
	while (count++ < 4)
	{
		if (!(get_next_line(fd, &line)))
			return (0);
		if (ft_strlen(line) != 4)
			return (0);
		if (!(*str = ft_strjoin(*str, line)))
			return (0);
	}
	return (1);
}

/*
** This function checks that block are valid and create
** string array of valid blocks
*/

int	check_file(int fd, char **blocks)
{
	char	*line;
	int	value;
	char	*str;
	char 	*temp;
	int	n;

	value = 1;
	n = 0;
	if (!(str = ft_strnew(1)))
		return (0);
	while (value == 1)
	{
		if (check_lines(&str, line, fd, n) != 1)
			return (0);
		value = get_next_line(fd, &line);
		if (!(ft_strlen(line) == 0) || check_block_chars(str) == 0 || !(temp = ft_strdup(str)))
			return (0);
		blocks[n++] = temp;
		ft_strclr(str);

	}
	blocks[n] = 0;
	ft_strdel(&str);
	return (1);
}
