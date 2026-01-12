/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_door_textures(t_game *game)
{
	game->door_closed_texture.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/fusuma_door_detailed.xpm",
			&game->door_closed_texture.width,
			&game->door_closed_texture.height);
	game->door_open_texture.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/fusuma_door_detailed.xpm",
			&game->door_open_texture.width,
			&game->door_open_texture.height);
	if (!game->door_closed_texture.img || !game->door_open_texture.img)
		return (0);
	game->door_closed_texture.addr = mlx_get_data_addr(
			game->door_closed_texture.img,
			&game->door_closed_texture.bits_per_pixel,
			&game->door_closed_texture.line_length,
			&game->door_closed_texture.endian);
	game->door_open_texture.addr = mlx_get_data_addr(
			game->door_open_texture.img,
			&game->door_open_texture.bits_per_pixel,
			&game->door_open_texture.line_length,
			&game->door_open_texture.endian);
	return (1);
}
