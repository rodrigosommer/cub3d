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

static int	load_sprite_images(t_game *game)
{
	game->sprite_textures[0].img = mlx_xpm_file_to_image(game->mlx,
			"./textures/dogmau_fundorosa.xpm",
			&game->sprite_textures[0].width,
			&game->sprite_textures[0].height);
	game->sprite_textures[1].img = NULL;
	game->sprite_textures[2].img = NULL;
	game->sprite_textures[3].img = NULL;
	game->sprite_textures[4].img = mlx_xpm_file_to_image(game->mlx,
			"./textures/dogmaumorto.xpm", &game->sprite_textures[4].width,
			&game->sprite_textures[4].height);
	game->sprite_textures[5].img = mlx_xpm_file_to_image(game->mlx,
			"./textures/dogmau_fundorosa.xpm",
			&game->sprite_textures[5].width,
			&game->sprite_textures[5].height);
	if (!game->sprite_textures[0].img || !game->sprite_textures[4].img
		|| !game->sprite_textures[5].img)
		return (0);
	return (1);
}

static void	get_texture_addr(t_game *game, int i)
{
	game->sprite_textures[i].addr = mlx_get_data_addr(
			game->sprite_textures[i].img,
			&game->sprite_textures[i].bits_per_pixel,
			&game->sprite_textures[i].line_length,
			&game->sprite_textures[i].endian);
}

static void	load_sprite_addrs(t_game *game)
{
	get_texture_addr(game, 0);
	get_texture_addr(game, 4);
	get_texture_addr(game, 5);
}

int	load_sprite_textures(t_game *game)
{
	if (!load_sprite_images(game))
		return (0);
	load_sprite_addrs(game);
	if (!game->sprite_textures[0].img)
		printf("[ERRO] Textura 0 não carregada!\n");
	else
		printf("[DEBUG] Textura 0 carregada com sucesso!\n");
	return (1);
}
