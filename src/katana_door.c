/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   katana_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*find_facing_door_katana(t_game *game)
{
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	t_door	*door;

	ray_x = game->player.x + game->player.dir_x * 0.8;
	ray_y = game->player.y + game->player.dir_y * 0.8;
	map_x = (int)ray_x;
	map_y = (int)ray_y;
	if (map_x >= 0 && map_x < game->map_width
		&& map_y >= 0 && map_y < game->map_height)
	{
		if (game->map[map_y][map_x] == 'D' || game->map[map_y][map_x] == 'O')
		{
			door = find_door(game, map_x, map_y);
			if (door)
				return (door);
		}
	}
	return (NULL);
}

void	toggle_door(t_door *door)
{
	printf("Door found! Current state: %d\n", door->state);
	if (door->state == DOOR_CLOSED)
	{
		door->state = DOOR_OPENING;
		door->animation_timer = 0.0;
		printf("Opening door\n");
	}
	else if (door->state == DOOR_OPEN)
	{
		door->state = DOOR_CLOSING;
		door->animation_timer = 0.0;
		printf("Closing door\n");
	}
}
