/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player_dot(t_game *game)
{
	int	center_x;
	int	center_y;
	int	x;
	int	y;

	center_x = MINIMAP_SIZE / 2;
	center_y = MINIMAP_SIZE / 2;
	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			if (x * x + y * y <= 4)
				draw_minimap_pixel(game, center_x + x, center_y + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_direction_line(t_game *game)
{
	int	center_x;
	int	center_y;
	int	i;

	center_x = MINIMAP_SIZE / 2;
	center_y = MINIMAP_SIZE / 2;
	i = 0;
	while (i <= 15)
	{
		draw_minimap_pixel(game, center_x + (int)(game->player.dir_x * i),
			center_y + (int)(game->player.dir_y * i), 0x00FF00);
		i++;
	}
}

void	draw_minimap_border(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINIMAP_SIZE)
	{
		draw_minimap_pixel(game, x, 0, 0xFFFFFF);
		draw_minimap_pixel(game, x, MINIMAP_SIZE - 1, 0xFFFFFF);
		x++;
	}
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		draw_minimap_pixel(game, 0, y, 0xFFFFFF);
		draw_minimap_pixel(game, MINIMAP_SIZE - 1, y, 0xFFFFFF);
		y++;
	}
}

void	render_minimap(t_game *game)
{
	draw_minimap_background(game);
	draw_minimap_border(game);
	draw_player_dot(game);
	draw_direction_line(game);
}
