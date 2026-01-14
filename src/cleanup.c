/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture_paths(char **paths)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (paths[i])
		{
			free(paths[i]);
			paths[i] = NULL;
		}
		i++;
	}
}

static void	destroy_single_texture(t_game *game, t_img *texture)
{
	if (!game->mlx || !texture->img)
		return ;
	mlx_destroy_image(game->mlx, texture->img);
	texture->img = NULL;
}

static void	destroy_extra_textures(t_game *game)
{
	destroy_single_texture(game, &game->floor_texture);
	destroy_single_texture(game, &game->ceiling_texture);
	destroy_single_texture(game, &game->door_closed_texture);
	destroy_single_texture(game, &game->door_open_texture);
	destroy_single_texture(game, &game->katana_texture);
}

static void	destroy_textures(t_game *game)
{
	int		i;

	if (!game->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		destroy_single_texture(game, &game->textures[i]);
		i++;
	}
	destroy_extra_textures(game);
}

void	cleanup_game(t_game *game)
{
	destroy_textures(game);
	free_texture_paths(game->texture_paths);
	free_map(game->map);
	if (game->img.img && game->mlx)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
}
