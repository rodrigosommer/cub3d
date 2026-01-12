/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_door_blocking(t_game *game, int x, int y)
{
	if (game->map[y][x] != 'D' && game->map[y][x] != 'O')
		return (0);
	return (!is_door_open(game, x, y));
}

static int	check_collision_loop(t_game *game, int *bounds, int i, int j)
{
	while (i <= bounds[3])
	{
		j = bounds[0];
		while (j <= bounds[1])
		{
			if (game->map[i][j] == '1' || is_door_blocking(game, j, i))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_collision(t_game *game, double x, double y, double buffer)
{
	int	bounds[4];

	bounds[0] = (int)(x - buffer);
	bounds[1] = (int)(x + buffer);
	bounds[2] = (int)(y - buffer);
	bounds[3] = (int)(y + buffer);
	if (bounds[0] < 0 || bounds[1] >= game->map_width
		|| bounds[2] < 0 || bounds[3] >= game->map_height)
		return (1);
	return (check_collision_loop(game, bounds, bounds[2], bounds[0]));
}

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	buffer;

	buffer = 0.3;
	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (!check_collision(game, new_x, game->player.y, buffer))
		game->player.x = new_x;
	else if (!check_collision(game, game->player.x + move_x * 0.5,
			game->player.y, buffer))
		game->player.x = game->player.x + move_x * 0.5;
	if (!check_collision(game, game->player.x, new_y, buffer))
		game->player.y = new_y;
	else if (!check_collision(game, game->player.x,
			game->player.y + move_y * 0.5, buffer))
		game->player.y = game->player.y + move_y * 0.5;
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}
