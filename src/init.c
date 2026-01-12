/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		error_exit("Failed to initialize MLX");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
	{
		error_exit("Failed to create window");
		return (0);
	}
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
	{
		error_exit("Failed to create image");
		return (0);
	}
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	return (1);
}

static int	load_all_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		load_texture(game, i, game->texture_paths[i]);
		if (!game->textures[i].img)
		{
			error_exit("Failed to load texture");
			return (0);
		}
		i++;
	}
	return (1);
}

static void	load_floor_ceiling_textures(t_game *game)
{
	game->floor_texture.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/floor.xpm", &game->floor_texture.width,
			&game->floor_texture.height);
	if (game->floor_texture.img)
		game->floor_texture.addr = mlx_get_data_addr(game->floor_texture.img,
				&game->floor_texture.bits_per_pixel,
				&game->floor_texture.line_length, &game->floor_texture.endian);
	game->ceiling_texture.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/ceiling.xpm", &game->ceiling_texture.width,
			&game->ceiling_texture.height);
	if (game->ceiling_texture.img)
		game->ceiling_texture.addr = mlx_get_data_addr(
				game->ceiling_texture.img,
				&game->ceiling_texture.bits_per_pixel,
				&game->ceiling_texture.line_length,
				&game->ceiling_texture.endian);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press_smooth, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_smooth, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
}

int	init_game(t_game *game)
{
	if (!init_mlx(game))
		return (0);
	if (!load_all_textures(game))
		return (0);
	load_sprite_textures(game);
	load_door_textures(game);
	load_floor_ceiling_textures(game);
	load_katana_texture(game);
	game->katana_slash_active = 0;
	game->katana_slash_timer = 0.0;
	init_doors(game);
	game->game_time = 0.0;
	game->rainbow_enabled = 1;
	game->rainbow_speed = 50.0;
	game->rainbow_intensity = 0.3;
	game->rainbow_position_factor = 10.0;
	game->tombstone_x = 0;
	game->tombstone_y = 0;
	game->has_tombstone = 0;
	game->level_completed = 0;
	game->victory_reason = 0;
	init_keys(game);
	setup_hooks(game);
	return (1);
}
