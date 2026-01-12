/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_door_collision(t_game *game, double x, double y, double b)
{
	if ((game->map[(int)(y + b)][(int)(x + b)] == 'D'
			&& !is_door_open(game, (int)(x + b), (int)(y + b)))
		|| (game->map[(int)(y + b)][(int)(x - b)] == 'D'
			&& !is_door_open(game, (int)(x - b), (int)(y + b)))
		|| (game->map[(int)(y - b)][(int)(x + b)] == 'D'
			&& !is_door_open(game, (int)(x + b), (int)(y - b)))
		|| (game->map[(int)(y - b)][(int)(x - b)] == 'D'
			&& !is_door_open(game, (int)(x - b), (int)(y - b))))
		return (1);
	return (0);
}

int	check_sprite_collision(t_game *game, double x, double y)
{
	double	buffer;

	buffer = 0.3;
	if (x + buffer >= game->map_width || x - buffer < 0
		|| y + buffer >= game->map_height || y - buffer < 0)
		return (1);
	if (game->map[(int)(y + buffer)][(int)(x + buffer)] == '1'
		|| game->map[(int)(y + buffer)][(int)(x - buffer)] == '1'
		|| game->map[(int)(y - buffer)][(int)(x + buffer)] == '1'
		|| game->map[(int)(y - buffer)][(int)(x - buffer)] == '1')
		return (1);
	if (check_door_collision(game, x, y, buffer))
		return (1);
	return (0);
}
