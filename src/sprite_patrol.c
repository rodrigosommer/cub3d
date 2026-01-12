/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_patrol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_to_target(t_game *game, t_sprite *sprite, double dx, double dy)
{
	double	dist;
	double	new_x;
	double	new_y;

	dist = sqrt(dx * dx + dy * dy);
	if (dist > 0.1)
	{
		dx /= dist;
		dy /= dist;
		new_x = sprite->x + dx * sprite->move_speed * 0.7;
		new_y = sprite->y + dy * sprite->move_speed * 0.7;
		if (!check_sprite_collision(game, new_x, sprite->y))
			sprite->x = new_x;
		if (!check_sprite_collision(game, sprite->x, new_y))
			sprite->y = new_y;
	}
}

static void	update_patrol_target(t_sprite *sprite)
{
	sprite->target_x = sprite->x + (rand() % 300 - 150) / 100.0;
	sprite->target_y = sprite->y + (rand() % 300 - 150) / 100.0;
	sprite->move_timer = 0.0;
}

void	aggressive_patrol_behavior(t_game *game, t_sprite *sprite)
{
	double	dx;
	double	dy;

	if (sprite->is_dead)
		return ;
	sprite->move_timer += 0.016;
	if (sprite->move_timer > 2.0)
		update_patrol_target(sprite);
	if (fabs(sprite->x - sprite->target_x) > 0.1
		|| fabs(sprite->y - sprite->target_y) > 0.1)
	{
		dx = sprite->target_x - sprite->x;
		dy = sprite->target_y - sprite->y;
		move_to_target(game, sprite, dx, dy);
	}
}
