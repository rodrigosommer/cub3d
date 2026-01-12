/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprites(t_game *game)
{
	game->num_sprites = 6;
	init_aggressive_dog(&game->sprites[0], 5.5, 5.5, 8.0);
	init_berserker_dog(&game->sprites[1], 8.5, 3.5);
	init_samurai_crocodile(&game->sprites[2], 12.5, 7.5);
	init_muscular_belgian_dog(&game->sprites[3], 3.5, 8.5);
	init_armored_samurai(&game->sprites[4], 15.5, 2.5);
	init_aggressive_dog(&game->sprites[5], 6.5, 12.5, 6.0);
	init_tombstone_sprite(game);
}

void	init_tombstone_sprite(t_game *game)
{
	int	idx;

	if (!game->has_tombstone)
		return ;
	idx = game->num_sprites;
	game->sprites[idx].x = game->tombstone_x;
	game->sprites[idx].y = game->tombstone_y;
	game->sprites[idx].texture_id = 5;
	game->sprites[idx].frame = 0;
	game->sprites[idx].is_aggressive = 0;
	game->sprites[idx].is_dead = 0;
	game->sprites[idx].health = 9999;
	game->sprites[idx].move_speed = 0;
	game->sprites[idx].vel_x = 0;
	game->sprites[idx].vel_y = 0;
	game->num_sprites++;
}

void	update_sprites(t_game *game)
{
	int	i;

	game->game_time += 0.016;
	i = 0;
	while (i < game->num_sprites)
	{
		update_sprite_animation(&game->sprites[i]);
		update_sprite_ai(game, &game->sprites[i]);
		i++;
	}
}

void	update_sprite_ai(t_game *game, t_sprite *sprite)
{
	aggressive_patrol_behavior(game, sprite);
}
