/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	expand_map_capacity(char ***temp_map, int *capacity)
{
	char	**new_map;

	*capacity *= 2;
	new_map = malloc(sizeof(char *) * (*capacity));
	if (!new_map)
		return (0);
	ft_memcpy(new_map, *temp_map, sizeof(char *) * (*capacity / 2));
	free(*temp_map);
	*temp_map = new_map;
	return (1);
}

void	cleanup_map_on_error(char **temp_map, int y)
{
	while (y >= 0)
		free(temp_map[y--]);
	free(temp_map);
}

void	set_north_direction(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

void	set_south_direction(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

int	handle_player_char(char c, int *player_found, char *player_dir)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*player_found)
		{
			error_exit("Multiple player positions found");
			return (0);
		}
		*player_dir = c;
		*player_found = 1;
	}
	return (1);
}
