/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_empty_space(int x, int y, t_game *game)
{
	if (is_border_position(x, y, game))
	{
		error_exit("Map not surrounded by walls");
		return (0);
	}
	if (!check_position(x - 1, y, game)
		|| !check_position(x + 1, y, game)
		|| !check_position(x, y - 1, game)
		|| !check_position(x, y + 1, game))
	{
		error_exit("Map not properly enclosed");
		return (0);
	}
	return (1);
}

static int	validate_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == '0')
			{
				if (!validate_empty_space(x, y, game))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!player_exists(game))
		return (0);
	if (!validate_walls(game))
		return (0);
	return (1);
}
