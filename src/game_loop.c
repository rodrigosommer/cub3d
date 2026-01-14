/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	process_movement(game);
	update_doors(game);
	if (game->katana_slash_active)
	{
		game->katana_slash_timer += 0.016;
		if (game->katana_slash_timer >= 0.3)
		{
			game->katana_slash_active = 0;
			game->katana_slash_timer = 0.0;
		}
	}
	render_frame(game);
	return (0);
}

void	init_keys(t_game *game)
{
	int	i;

	i = 0;
	while (i < 65536)
	{
		game->keys[i] = 0;
		i++;
	}
}
