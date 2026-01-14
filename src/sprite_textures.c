/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/10/13 18:19:20 by mlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_sprite_textures(t_game *game)
{
	int	index;

	index = 0;
	while (index < 6)
	{
		game->sprite_textures[index].img = NULL;
		game->sprite_textures[index].addr = NULL;
		game->sprite_textures[index].bits_per_pixel = 0;
		game->sprite_textures[index].line_length = 0;
		game->sprite_textures[index].endian = 0;
		game->sprite_textures[index].width = 0;
		game->sprite_textures[index].height = 0;
		index++;
	}
	return (1);
}
