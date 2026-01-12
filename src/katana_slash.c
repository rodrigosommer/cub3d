/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   katana_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	damage_sprite(t_game *game, int i)
{
	game->sprites[i].slices_received++;
	game->sprites[i].is_split = 1;
	game->sprites[i].split_timer = 0.0;
	printf("Hit sprite %d! Sprite killed instantly!\n", i);
	game->sprites[i].is_dead = 1;
	game->sprites[i].texture_id = 4;
	game->sprites[i].health = 0;
}

static void	check_sprite_hit(t_game *game, double ray_x, double ray_y)
{
	int		i;
	double	distance;

	i = 0;
	while (i < game->num_sprites)
	{
		printf("Checking sprite %d at position: %.2f, %.2f\n",
			i, game->sprites[i].x, game->sprites[i].y);
		distance = sqrt((game->sprites[i].x - ray_x)
				* (game->sprites[i].x - ray_x)
				+ (game->sprites[i].y - ray_y)
				* (game->sprites[i].y - ray_y));
		printf("Distance to sprite %d: %.2f (health: %d, texture_id: %d)\n",
			i, distance, game->sprites[i].health, game->sprites[i].texture_id);
		if (distance < 2.5 && !game->sprites[i].is_dead)
			damage_sprite(game, i);
		i++;
	}
}

void	damage_sprites(t_game *game)
{
	double	ray_x;
	double	ray_y;

	ray_x = game->player.x + game->player.dir_x * 2.0;
	ray_y = game->player.y + game->player.dir_y * 2.0;
	printf("Katana attack at position: %.2f, %.2f\n", ray_x, ray_y);
	check_sprite_hit(game, ray_x, ray_y);
}

void	handle_katana_slash(t_game *game)
{
	t_door	*door;

	printf("Katana slash activated!\n");
	door = find_facing_door_katana(game);
	if (door)
		toggle_door(door);
	else
	{
		printf("No door found, attacking sprites\n");
		damage_sprites(game);
		game->katana_slash_active = 1;
		game->katana_slash_timer = 0.0;
	}
}
