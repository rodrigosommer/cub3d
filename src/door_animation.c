/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_opening_door(t_game *game, t_door *door)
{
	door->animation_timer += 0.016;
	door->animation_progress = door->animation_timer / 1.0;
	if (door->animation_progress >= 1.0)
	{
		door->animation_progress = 1.0;
		door->state = DOOR_OPEN;
		game->map[door->y][door->x] = 'O';
	}
}

static void	update_closing_door(t_game *game, t_door *door)
{
	door->animation_timer += 0.016;
	door->animation_progress = 1.0 - (door->animation_timer / 1.0);
	if (door->animation_progress <= 0.0)
	{
		door->animation_progress = 0.0;
		door->state = DOOR_CLOSED;
		game->map[door->y][door->x] = 'D';
	}
}

void	update_doors(t_game *game)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < game->num_doors)
	{
		door = &game->doors[i];
		if (door->state == DOOR_OPENING)
			update_opening_door(game, door);
		else if (door->state == DOOR_CLOSING)
			update_closing_door(game, door);
		i++;
	}
}

int	is_door_open(t_game *game, int x, int y)
{
	t_door	*door;

	door = find_door(game, x, y);
	if (!door)
		return (0);
	return (door->state == DOOR_OPEN || door->animation_progress > 0.8);
}
