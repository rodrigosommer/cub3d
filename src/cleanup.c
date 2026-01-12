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

static void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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

static void	destroy_textures(t_game *game)
{
	int	i;

	if (!game->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
	if (game->floor_texture.img)
	{
		mlx_destroy_image(game->mlx, game->floor_texture.img);
		game->floor_texture.img = NULL;
	}
	if (game->ceiling_texture.img)
	{
		mlx_destroy_image(game->mlx, game->ceiling_texture.img);
		game->ceiling_texture.img = NULL;
	}
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
