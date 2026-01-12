/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling_floor(t_game *game)
{
	int	x;
	int	y;
	int	pitch_offset;
	int	horizon;

	pitch_offset = (int)(game->player.pitch * 200);
	horizon = HEIGHT / 2 + pitch_offset;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < horizon)
				put_pixel(&game->img, x, y, game->ceiling_color);
			else
				put_pixel(&game->img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	draw_ceiling_floor(game);
	raycasting(game);
	render_sprites(game);
	render_katana_hands(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	if (game->level_completed)
		render_victory_screen(game);
	return (0);
}
