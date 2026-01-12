/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_border_position(int x, int y, t_game *game)
{
	return (x == 0 || y == 0 || x == game->map_width - 1
		|| y == game->map_height - 1);
}

int	check_position(int x, int y, t_game *game)
{
	if (y < 0 || y >= game->map_height || x < 0
		|| x >= (int)ft_strlen(game->map[y]))
		return (0);
	if (game->map[y][x] == ' ')
		return (0);
	if (game->map[y][x] == '1' || game->map[y][x] == 'D')
		return (1);
	return (game->map[y][x] == '0' || game->map[y][x] == 'O');
}

int	player_exists(t_game *game)
{
	if (game->player.x == 0 && game->player.y == 0)
	{
		error_exit("No player position found");
		return (0);
	}
	return (1);
}
