/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   katana.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_katana_transparency(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < game->katana_texture.height)
	{
		x = 0;
		while (x < game->katana_texture.width)
		{
			color = get_texture_pixel(&game->katana_texture, x, y);
			if (color == 0xFF00FF)
				put_pixel(&game->katana_texture, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

int	load_katana_texture(t_game *game)
{
	game->katana_texture.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/katana.xpm", &game->katana_texture.width,
			&game->katana_texture.height);
	if (!game->katana_texture.img)
		return (0);
	game->katana_texture.addr = mlx_get_data_addr(game->katana_texture.img,
			&game->katana_texture.bits_per_pixel,
			&game->katana_texture.line_length,
			&game->katana_texture.endian);
	process_katana_transparency(game);
	return (1);
}
