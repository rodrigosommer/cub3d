/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   victory_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/12 00:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_overlay(t_game *game)
{
	int	x;
	int	y;
	int	color;

	color = 0x88000000;
	y = HEIGHT / 3;
	while (y < 2 * HEIGHT / 3)
	{
		x = WIDTH / 4;
		while (x < 3 * WIDTH / 4)
		{
			put_pixel(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_victory_screen(t_game *game)
{
	char	*message;

	if (!game->level_completed)
		return ;
	draw_overlay(game);
	if (game->victory_reason == 1)
		message = "LEVEL COMPLETE - TOMBSTONE REACHED!";
	else
		message = "LEVEL COMPLETE - ALL ENEMIES DEFEATED!";
	mlx_string_put(game->mlx, game->win, WIDTH / 2 - 200, HEIGHT / 2 - 20,
		0xFFFFFF, message);
	mlx_string_put(game->mlx, game->win, WIDTH / 2 - 150, HEIGHT / 2 + 20,
		0xFFFFFF, "Press ENTER to continue");
}
