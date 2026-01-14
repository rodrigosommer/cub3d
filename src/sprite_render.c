/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/10/09 18:35:00 by mlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sprite_screen_pos(t_game *game, t_sprite *sprite,
	int *sprite_screen_x, double *sprite_size)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;

	sprite_x = sprite->x - game->player.x;
	sprite_y = sprite->y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	*sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	*sprite_size = ft_abs((int)(HEIGHT / transform_y)) * 0.5;
}

void	calc_sprite_bounds(int *start_x, int *end_x,
	int sprite_screen_x, double sprite_size)
{
	*start_x = sprite_screen_x - (int)sprite_size / 2;
	*end_x = sprite_screen_x + (int)sprite_size / 2;
	if (*start_x < 0)
		*start_x = 0;
	if (*end_x >= WIDTH)
		*end_x = WIDTH - 1;
}
