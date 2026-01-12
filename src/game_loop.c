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

static void	check_tombstone_victory(t_game *game)
{
	double	dist;

	if (!game->has_tombstone)
		return ;
	dist = sqrt((game->player.x - game->tombstone_x)
			* (game->player.x - game->tombstone_x)
			+ (game->player.y - game->tombstone_y)
			* (game->player.y - game->tombstone_y));
	if (dist < 1.5)
	{
		game->level_completed = 1;
		game->victory_reason = 1;
	}
}

static void	check_enemies_victory(t_game *game)
{
	int	i;
	int	all_enemies_dead;

	all_enemies_dead = 1;
	i = -1;
	while (++i < game->num_sprites)
	{
		if (game->sprites[i].health < 9999 && !game->sprites[i].is_dead)
		{
			all_enemies_dead = 0;
			break ;
		}
	}
	if (all_enemies_dead && game->num_sprites > 0)
	{
		game->level_completed = 1;
		game->victory_reason = 2;
	}
}

void	check_victory_conditions(t_game *game)
{
	if (game->level_completed)
		return ;
	check_tombstone_victory(game);
	if (!game->level_completed)
		check_enemies_victory(game);
}

int	game_loop(t_game *game)
{
	if (!game->level_completed)
	{
		process_movement(game);
		update_sprites(game);
		update_doors(game);
		check_victory_conditions(game);
	}
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
