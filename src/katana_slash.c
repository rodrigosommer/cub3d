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

void	damage_sprites(t_game *game)
{
	(void)game;
}

void	handle_katana_slash(t_game *game)
{
	t_door	*door;

	printf("Katana slash activated!\n");
	door = find_facing_door_katana(game);
	if (door)
		toggle_door(door);
	game->katana_slash_active = 1;
	game->katana_slash_timer = 0.0;
}
