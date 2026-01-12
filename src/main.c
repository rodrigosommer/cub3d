/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_struct(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->floor_color = -1;
	game->ceiling_color = -1;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = NULL;
		game->texture_paths[i] = NULL;
		i++;
	}
}

static int	validate_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		error_exit("Usage: ./cub3D <map.cub>");
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		error_exit("Map file must have .cub extension");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_args(argc, argv))
		return (1);
	init_game_struct(&game);
	if (!parse_file(argv[1], &game))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!validate_map(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!init_game(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	render_frame(&game);
	mlx_loop(game.mlx);
	return (0);
}
