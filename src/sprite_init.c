/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_aggressive_dog(t_sprite *sprite, double x, double y,
	double aggro_dist)
{
	sprite->x = x;
	sprite->y = y;
	sprite->vel_x = 0.0;
	sprite->vel_y = 0.0;
	sprite->target_x = x;
	sprite->target_y = y;
	sprite->texture_id = 0;
	sprite->frame = 0;
	sprite->anim_timer = 0.0;
	sprite->move_timer = 0.0;
	sprite->is_aggressive = 1;
	sprite->aggro_distance = aggro_dist;
	sprite->move_speed = 0.08;
	sprite->health = 150;
	sprite->is_split = 0;
	sprite->split_timer = 0.0;
	sprite->slices_received = 0;
	sprite->is_dead = 0;
}

void	init_berserker_dog(t_sprite *sprite, double x, double y)
{
	sprite->x = x;
	sprite->y = y;
	sprite->vel_x = 0.0;
	sprite->vel_y = 0.0;
	sprite->target_x = x;
	sprite->target_y = y;
	sprite->texture_id = 1;
	sprite->frame = 0;
	sprite->anim_timer = 0.0;
	sprite->move_timer = 0.0;
	sprite->is_aggressive = 1;
	sprite->aggro_distance = 12.0;
	sprite->move_speed = 0.12;
	sprite->health = 200;
	sprite->is_split = 0;
	sprite->split_timer = 0.0;
	sprite->slices_received = 0;
	sprite->is_dead = 0;
}

void	init_samurai_crocodile(t_sprite *sprite, double x, double y)
{
	sprite->x = x;
	sprite->y = y;
	sprite->vel_x = 0.0;
	sprite->vel_y = 0.0;
	sprite->target_x = x;
	sprite->target_y = y;
	sprite->texture_id = 0;
	sprite->frame = 0;
	sprite->anim_timer = 0.0;
	sprite->move_timer = 0.0;
	sprite->is_aggressive = 1;
	sprite->aggro_distance = 15.0;
	sprite->move_speed = 0.06;
	sprite->health = 300;
	sprite->is_split = 0;
	sprite->split_timer = 0.0;
	sprite->slices_received = 0;
	sprite->is_dead = 0;
}
