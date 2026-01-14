/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		center_y;
	int		delta_x;
	double	rotation;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	delta_x = x - center_x;
	(void)y;
	if (delta_x != 0)
	{
		rotation = delta_x * 0.003;
		rotate_player(game, rotation);
	}
	game->player.pitch = 0.0;
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	return (0);
}
