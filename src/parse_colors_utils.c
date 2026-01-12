/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_number(char **str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while ((**str >= '0' && **str <= '9') && i < 3)
	{
		num = num * 10 + (**str - '0');
		(*str)++;
		i++;
	}
	if (i == 0 || num > 255)
		return (-1);
	return (num);
}

int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	parse_rgb_values(char *line, int *color)
{
	char	*ptr;
	int		r;
	int		g;
	int		b;

	ptr = line + 1;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	r = parse_number(&ptr);
	if (r == -1 || *ptr != ',')
		return (0);
	ptr++;
	g = parse_number(&ptr);
	if (g == -1 || *ptr != ',')
		return (0);
	ptr++;
	b = parse_number(&ptr);
	if (b == -1)
		return (0);
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (*ptr && *ptr != '\n')
		return (0);
	*color = create_color(r, g, b);
	return (1);
}
