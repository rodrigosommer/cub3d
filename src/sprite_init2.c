/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_muscular_belgian_dog(t_sprite *sprite, double x, double y)
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
	sprite->aggro_distance = 6.0;
	sprite->move_speed = 0.15;
	sprite->health = 120;
	sprite->is_split = 0;
	sprite->split_timer = 0.0;
	sprite->slices_received = 0;
	sprite->is_dead = 0;
}

void	init_armored_samurai(t_sprite *sprite, double x, double y)
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
	sprite->aggro_distance = 10.0;
	sprite->move_speed = 0.08;
	sprite->health = 400;
	sprite->is_split = 0;
	sprite->split_timer = 0.0;
	sprite->slices_received = 0;
	sprite->is_dead = 0;
}

void	init_sprite(t_game *game, int x, int y)
{
	if (game->num_sprites >= MAX_SPRITES)
		return ;
	game->sprites[game->num_sprites].x = x + 0.5;
	game->sprites[game->num_sprites].y = y + 0.5;
	game->sprites[game->num_sprites].vel_x = 0.0;
	game->sprites[game->num_sprites].vel_y = 0.0;
	game->sprites[game->num_sprites].target_x = x + 0.5;
	game->sprites[game->num_sprites].target_y = y + 0.5;
	game->sprites[game->num_sprites].texture_id = 0;
	game->sprites[game->num_sprites].frame = 0;
	game->sprites[game->num_sprites].anim_timer = 0.0;
	game->sprites[game->num_sprites].move_timer = 0.0;
	game->sprites[game->num_sprites].is_aggressive = 1;
	game->sprites[game->num_sprites].aggro_distance = 8.0;
	game->sprites[game->num_sprites].move_speed = 0.08;
	game->sprites[game->num_sprites].health = 100;
	game->sprites[game->num_sprites].is_split = 0;
	game->sprites[game->num_sprites].split_timer = 0.0;
	game->sprites[game->num_sprites].slices_received = 0;
	game->sprites[game->num_sprites].is_dead = 0;
	game->num_sprites++;
}
